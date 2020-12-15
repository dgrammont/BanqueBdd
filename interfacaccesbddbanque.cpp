#include "interfacaccesbddbanque.h"
/**
* @date 11/12/20
* @author dylan grammont
* @file interfaccesbddbanque.cpp
* @copyright moi
* @version 1.0
*/

/**
 * @brief InterfacAccesBDDBanque::InterfacAccesBDDBanque
 * @param hote
 * @param bd
 * @param login
 * @param mdp
 * constructeur de l'interface bdd
 * permet la connection dbb avec un fichier ini
 */
InterfacAccesBDDBanque::InterfacAccesBDDBanque(QString hote, QString bd, QString login, QString mdp)
{
    FichierIni();

    bdd=QSqlDatabase::addDatabase("QMYSQL");
    bdd.setHostName(infoBdd.hote);
    bdd.setDatabaseName(infoBdd.bd);
    bdd.setUserName(infoBdd.login);
    bdd.setPassword(infoBdd.mdp);
    if(!bdd.open())
    {
        QMessageBox message;

        qDebug()<<"pb acces bd"<<bdd.lastError();
    }
    else
    {
        qDebug()<<"connecté";
    }
}
/**
 * @brief InterfacAccesBDDBanque::ObtenirSolde
 * @param numCompte
 * @return
 * retourne le solde de la bdd
 */
float InterfacAccesBDDBanque::ObtenirSolde(int numCompte)
{
    float retour=0;
    qDebug()<<this<<"obtenir solde"<<numCompte;
    // preparation de la requete
    QSqlQuery requetePrepare;
    requetePrepare.prepare("select solde from comptes where idCompte=:nro ;");
    requetePrepare.bindValue(":nro",numCompte);
    if(!requetePrepare.exec())
    {
        qDebug()<<"pb requete"<<requetePrepare.lastError();
    }
    else
    {
        requetePrepare.next();
        retour =requetePrepare.value("solde").toFloat();

    }
    qDebug()<<retour;
    return retour;
}
/**
 * @brief InterfacAccesBDDBanque::MettreAJourLeSolde
 * @param numCompte
 * @param nouveauSolde
 * Met a joue le solde de la bdd
 */
void InterfacAccesBDDBanque::MettreAJourLeSolde(int numCompte, float nouveauSolde)
{
    QSqlQuery requetePrepare;
    qDebug()<<this<<"Mettre a jour solde"<<numCompte;
    requetePrepare.prepare("update comptes set solde = :nsolde where idCompte = :nbcompte");
    requetePrepare.bindValue(":nsolde",nouveauSolde);
    requetePrepare.bindValue(":nbcompte",numCompte);
    if(!requetePrepare.exec())
    {
        qDebug()<<"pb requete"<<requetePrepare.lastError();
    }
    else
    {
        requetePrepare.next();
    }
}
/**
 * @brief InterfacAccesBDDBanque::CreerCompte
 * @param numCompte
 * @param nom
 * @param prenom
 * @param ville
 * @param idAgence
 * permet de crée un compte
 */
void InterfacAccesBDDBanque::CreerCompte(typeClient client)
{
    if(!CompteExiste(client.numKompte)){
        QSqlQuery requetePrepare;
        qDebug()<<this<<"creer compte"<<client.numKompte;
        requetePrepare.prepare("insert into comptes (idCompte,nom,prenom,Ville,id_agence) values (:nro,:nom,:prenom,:ville,:agence)");
        requetePrepare.bindValue(":nom",client.nom);
        requetePrepare.bindValue(":prenom",client.prenom);
        requetePrepare.bindValue(":ville",client.ville);
        requetePrepare.bindValue(":agence",client.agence);
        requetePrepare.bindValue(":nro",client.numKompte);
        if(!requetePrepare.exec())
        {
            qDebug()<<"pb requete"<<requetePrepare.lastError();
        }
        else
        {
            requetePrepare.next();
        }
    }
    else{
        qDebug()<<"le compte existe déjà";
    }
}
/**
 * @brief InterfacAccesBDDBanque::CompteExiste
 * @param numCompte
 * @return
 * permet de vérfié si le compte est present dans la bdd
 */
bool InterfacAccesBDDBanque::CompteExiste(int numCompte)
{
    QSqlQuery requete;
    qDebug()<<this<<"compte existe"<<numCompte;
    bool existe=false;
    requete.prepare("select solde from comptes where idCompte=:id;");
    requete.bindValue(":id",numCompte);
    if (!requete.exec()){
        qDebug()<<"pb requete compte existe "<<requete.lastError();
    }
    // si le compte existe on passe existe a vrai
    if (requete.size()!=0)
    {
        existe=true;
    }
    return existe;
}
/**
 * @brief InterfacAccesBDDBanque::FichierIni
 * permet de le lire le fichier ini et deamndé la création si il existe pas
 */
void InterfacAccesBDDBanque::FichierIni()
{
    QString nomFichierIni = "initialisationBDD.ini";
    QFileInfo fichierIni(nomFichierIni);
    if (fichierIni.exists() && fichierIni.isFile())
    {
        // à compléter la lecture du fichier
        QSettings paramsEqui(nomFichierIni,QSettings::IniFormat);
        infoBdd.hote=paramsEqui.value("informationBDD/hote").toString();
        infoBdd.bd=paramsEqui.value("informationBDD/bd").toString();
        infoBdd.login=paramsEqui.value("informationBDD/login").toString();
        infoBdd.mdp=paramsEqui.value("informationBDD/mdp").toString();

    }
    else // si le fichier n’existe pas, il est créé avec les valeurs par défaut
    {
        infoBdd.hote="172.18.58.14";
        infoBdd.bd="banque";
        infoBdd.login="snir";
        infoBdd.mdp="snir";

        // il est ensuite enregistré
        EnregistreFichierIni(infoBdd);

    }
}
/**
 * @brief InterfacAccesBDDBanque::EnregistreFichierIni
 * @param info
 * permet d'enregistré le fichier ini
 */
void InterfacAccesBDDBanque::EnregistreFichierIni(const typeInfoBdd info)
{

    QString nomFichierIni = "initialisationBDD.ini";
    // à compléter l’enregistrement du fichier
    QSettings paramsSocket(nomFichierIni,QSettings::IniFormat);
    paramsSocket.beginGroup("informationBDD");
    paramsSocket.setValue("hote",info.hote);
    paramsSocket.setValue("bd",info.bd);
    paramsSocket.setValue("login",info.login);
    paramsSocket.setValue("mdp",info.mdp);
    paramsSocket.endGroup();

}

QString InterfacAccesBDDBanque::DemandeNom(int numCompte)
{
    QString nom;
    QSqlQuery requete;
    requete.prepare("select nom from comptes where idCompte=:id;");
    requete.bindValue(":id",numCompte);
    if (!requete.exec()){
        qDebug()<<"pb requete compte existe "<<requete.lastError();
    }
    else
    {
        requete.next();
        nom = requete.value("nom").toString();
    }
    return nom;
}

QString InterfacAccesBDDBanque::DemandePrenom(int numCompte)
{
    QString prenom;
    QSqlQuery requete;
    requete.prepare("select  prenom from comptes where idCompte=:id;");
    requete.bindValue(":id",numCompte);
    if (!requete.exec()){
        qDebug()<<"pb requete compte existe "<<requete.lastError();
    }
    else
    {
        requete.next();
        prenom = requete.value("prenom").toString();
    }
    return prenom;
}

QString InterfacAccesBDDBanque::ObtenirAgences()
{
    QString list;

    QSqlQuery requete;
    requete.prepare("select nom from agences;");
    if (!requete.exec()){
        qDebug()<<"pb requete  agence "<<requete.lastError();
    }
    else
    {
        while (requete.next()) {
            list += requete.value("nom").toString() +";";
            qDebug()<<this<<"list avant chop : "<<list;
        }
        if(!list.isEmpty())
            list.chop(1);
    }
    qDebug()<<this<<"list : "<<list;
    return list;
}



