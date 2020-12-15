#ifndef SERVEURBANQUE_H
#define SERVEURBANQUE_H

#include "compteclient.h"
#include <QList>
#include <QTcpServer>
#include <QMessageBox>
#include <QDataStream>
#include <QBuffer>
#include <QByteArray>
#include "definiton.h"


/**
* @date 11/12/20
* @author dylan grammont
* @file banquemainwindow.cpp
* @copyright moi
* @version 1.0
*/



class ServeurBanque : public QTcpServer
{
    Q_OBJECT
public:
    ServeurBanque(QObject *parent=0);
    void Start();
    void Stop();
    void EnvoyerMessage(QChar commande, QString msg, CompteClient *client);
private:
    /**
     * @brief lesConnexionsClients
     * liste des client crée dynamiquement
     */
    QList<CompteClient*> lesConnexionsClients;
    /**
     * @brief nom
     */
    QString nom;
    /**
     * @brief prenom
     */
    QString prenom;
    /**
     * @brief ville
     */
    QString ville;
    /**
     * @brief idAgence
     */
    int idAgence;
    /**
     * @brief numCompte
     * numéro de compte
     */
    int numCompte;


private slots:
    /**
     * @brief onServeurBanque_newConnection
     * nouvelle conection
     */
    void onServeurBanque_newConnection();
    /**
     * @brief onCompteClient_disconnected
     * deconnection
     */
    void onCompteClient_disconnected();
    /**
     * @brief onCompteClient_readyRead
     * permet de lire les info recu
     */
    void onCompteClient_readyRead();
};

#endif // SERVEURBANQUE_H
