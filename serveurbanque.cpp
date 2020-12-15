#include "serveurbanque.h"

#include <QDebug>

/**
* @date 11/12/20
* @author dylan grammont
* @file serveurbanque.cpp
* @copyright moi
* @version 1.0
*/


/**
 * @brief ServeurBanque::ServeurBanque
 * @param parent
 * constructeur du serveur banque
 */
ServeurBanque::ServeurBanque(QObject *parent):
    QTcpServer(parent)
{
    connect(this,&QTcpServer::newConnection,this,&ServeurBanque::onServeurBanque_newConnection);

}
/**
 * @brief ServeurBanque::Start
 * démare le serveur
 */
void ServeurBanque::Start()
{
    QMessageBox message;
    if( !this->listen(QHostAddress::Any,8888)){
        message.setText("serveur sourd");
        message.exec();

    }else{


        qDebug()<<"serveur en écoute";

    }
}
/**
 * @brief ServeurBanque::Stop
 * Stop le serveur
 */
void ServeurBanque::Stop()
{
    this->close();
    lesConnexionsClients.clear();
}
/**
 * @brief ServeurBanque::EnvoyerMessage
 * @param msg
 * @param client
 * permet d'envoyer un message au client
 */
void ServeurBanque::EnvoyerMessage(QChar commande,QString msg, CompteClient *client)
{
    quint16 taille=0;
    QBuffer tampon;
    taille= msg.length();

    tampon.open(QIODevice::WriteOnly);
    //association du tampon au flux de sortie
    QDataStream out(&tampon);
    //construction de la trame
    out<<taille<<commande<<msg;
    //envoi du QByteArray du tampon via la socket
    taille=tampon.size()-sizeof(taille);
    //placement sur la première postion du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel da la trame
    out<<taille;
    //envoi du QByteArray du tampon via la socket
    client->write(tampon.buffer());

    qDebug()<<"envoyer message : "<<client->peerAddress();
}
/**
 * @brief ServeurBanque::onServeurBanque_newConnection
 * connection du client
 */
void ServeurBanque::onServeurBanque_newConnection()
{
    CompteClient *client;

    while (hasPendingConnections()!=false)
    {
        client=static_cast<CompteClient*>(this->nextPendingConnection());
        connect(client,&QTcpSocket::readyRead,this,&ServeurBanque::onCompteClient_readyRead);
        connect(client,&QTcpSocket::disconnected,this,&ServeurBanque::onCompteClient_disconnected);
        lesConnexionsClients.append(client);
        EnvoyerMessage('L',"Quel est votre numéro de compte ?",client);
        qDebug()<<"new connection : "<<client->peerAddress() ;
    }
}
/**
 * @brief ServeurBanque::onCompteClient_disconnected
 * deconnection du client
 */
void ServeurBanque::onCompteClient_disconnected()
{
    CompteClient *client=(CompteClient*)sender();
    if(!client){
        QMessageBox msg;
        msg.setText("erreur de connexion:"+client->errorString());
        msg.exec();
    }
    else
    {
        lesConnexionsClients.removeOne(client);client->deleteLater();
        qDebug()<<"deconnection : "<<client->peerAddress();
    }
}
/**
 * @brief ServeurBanque::onCompteClient_readyRead
 * switch des commande recu et des message depuis le client
 */
void ServeurBanque::onCompteClient_readyRead()
{
    CompteClient *client=(CompteClient*)sender();
    quint16 taille=0;
    float montant=0;
    int numCpt;
    QString message;


    QChar commande;

    QDataStream in(client);
    // si le nombre d'octets recu est au moin egal a celui de la taille de ce que l'on doit recevoir
    if(client->bytesAvailable()>=(qint64)sizeof (taille)){
        //association de la socket au flux d'entree


        // extraire la taille de ce que l'on doit recevoir
        in>>taille;
        //si le nombre d'octets recu est au moins egal a celui de ce l'on doit recevoir
        if(client->bytesAvailable()>=(quint64)taille){
            //extraire le message de la banque et le mettre dans message
            in>>commande;

        }
    }
    switch (commande.toLatin1())
    {



    case 'N':

        in>>numCpt;
        qDebug()<<this<<"cas N :"<<numCpt;
        if(client->bd.CompteExiste(numCpt)){

            EnvoyerMessage(commande,"Bienvenue : "+client->bd.DemandeNom(numCpt)+" "+client->bd.DemandePrenom(numCpt),client);
             qDebug()<<this<<"cas N :"<<numCompte;
        }else{

            EnvoyerMessage('A',client->bd.ObtenirAgences(),client);
             qDebug()<<this<<"cas A :"<<numCompte;
        }
        numCompte = numCpt;


        break;

    case 'R':
        in>>montant;
        if(client->Retirer(float(montant))){
            EnvoyerMessage(commande,"Votre nouveau solde est de : "+QString::number(client->ObtenirSolde()),client);
        }else{
            EnvoyerMessage(commande,"Le montant est supérieux au solde",client);
        }

        qDebug()<<this<<"cas R :"<<montant;
        break;

    case 'D':
        in>>montant;
        client->Deposer(float(montant));
        EnvoyerMessage(commande,"Votre nouveau solde est de : "+QString::number(client->ObtenirSolde()),client);
        qDebug()<<this<<"cas D :"<<montant;
        break;

    case 'S':
        in>>montant;
        EnvoyerMessage(commande,"Votre  solde est de :"+QString::number(client->bd.ObtenirSolde(numCompte)),client);
        qDebug()<<this<<"cas S :"<<client->bd.ObtenirSolde(numCompte);
        break;



    case 'Y':{
        typeClient clientStruc;
        in>>clientStruc.nom;
        in>>clientStruc.prenom;
        in>>clientStruc.ville;
        in>>clientStruc.agence;
        in>>clientStruc.numKompte;
        qDebug()<<this<<"cas Y :"<<clientStruc.nom<<clientStruc.prenom<<clientStruc.ville<<clientStruc.agence<<clientStruc.numKompte;
        EnvoyerMessage(commande,"Structur envoyer : ",client);
        client->DefinirNumCompte(clientStruc);
    }
        break;


    default:
        break;

    }
    qDebug()<<"commande : "<<commande;
    qDebug()<<"message : "<<montant;
    qDebug()<<"ready read : "<<client->peerAddress() ;
}

