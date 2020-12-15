#include "compteclient.h"

/**
* @date 11/12/20
* @author dylan grammont
* @file compteclient.cpp
* @copyright moi
* @version 1.0
*/

/**
 * @brief CompteClient::bd
 * constructeur de la classe client
 */
InterfacAccesBDDBanque CompteClient::bd("172.18.58.14","banque","snir","snir");
CompteClient::CompteClient(QObject *parent):
    QTcpSocket(parent)
{

}
/**
 * @brief CompteClient::Retirer
 * @param montant
 * @return
 * permet de retiré le motant voulu et vérifie si il supérieur au solde
 */
bool CompteClient::Retirer(float montant)
{
    solde = bd.ObtenirSolde(numCompte);
    bool verif;
    if(montant<bd.ObtenirSolde(numCompte)){
        verif = true;
        solde -= montant;
        bd.MettreAJourLeSolde(numCompte,solde);
    }else{
        verif = false;
    }
    return verif;
}
/**
 * @brief CompteClient::Deposer
 * @param montant
 * permet d'ajouter le montant désiré sur le compte
 */
void CompteClient::Deposer(float montant)
{
    solde = bd.ObtenirSolde(numCompte);
    solde += montant;
    bd.MettreAJourLeSolde(numCompte,solde);

}
/**
 * @brief CompteClient::ObtenirSolde
 * @return
 * retourne le solde depuis la bdd
 */
float CompteClient::ObtenirSolde()
{
    return bd.ObtenirSolde(numCompte);

}
/**
 * @brief CompteClient::ObtenirNumCompte
 * @return
 * retourne le numéro de compte
 */
int CompteClient::ObtenirNumCompte()
{

    return  numCompte;
}
/**
 * @brief CompteClient::DefinirNumCompte
 * @param _numCompte
 * @param nom
 * @param prenom
 * @param ville
 * @param idAgence
 * permet de crée un compte et de l'ajouter dans la bdd
 */
void CompteClient::DefinirNumCompte(typeClient client)
{

    bd.CreerCompte(client);
    numCompte = client.numKompte;
    solde = 200;
    bd.MettreAJourLeSolde(numCompte,200);


}
/**
 * @brief CompteClient::CompteExite
 * @param _numCompte
 * @return
 * verifi si le compte existe
 */
bool CompteClient::CompteExite(int _numCompte)
{
    bool compte = false;
    if(!bd.CompteExiste(_numCompte)){
        compte = true;

    }
    numCompte = _numCompte;

    return compte;

}
