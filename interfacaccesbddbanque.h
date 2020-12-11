#ifndef INTERFACACCESBDDBANQUE_H
#define INTERFACACCESBDDBANQUE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QFileInfo>
#include <QSettings>
#include <QDataStream>
#include <QFileDialog>
/**
* @date 11/12/20
* @author dylan grammont
* @file interfaccesbddbanque.h
* @copyright moi
* @version 1.0
*/
typedef struct{
    QString hote;
    QString bd;
    QString login;
    QString mdp;
}typeInfoBdd;

class InterfacAccesBDDBanque
{
public:
    InterfacAccesBDDBanque(QString hote,QString bd,QString login,QString mdp);
    float ObtenirSolde(int numCompte);
    void MettreAJourLeSolde(int numCompte,float nouveauSolde);
    void CreerCompte(int numCompte, QString nom,QString prenom, QString ville,int idAgence);
    bool CompteExiste(int numCompte);
    void FichierIni();
    void EnregistreFichierIni(const typeInfoBdd info);
private:
    /**
      * @brief bdd
      * la basse de donnée
      */
     QSqlDatabase bdd;
     /**
      * @brief infoBdd
      * les info du fichier ini
      */
     typeInfoBdd infoBdd;
};

#endif // INTERFACACCESBDDBANQUE_H
