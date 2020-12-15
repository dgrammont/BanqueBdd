#ifndef COMPTECLIENT_H
#define COMPTECLIENT_H
#include <QTcpSocket>
#include <interfacaccesbddbanque.h>
#include "definiton.h"

/**
* @date 11/12/20
* @author dylan grammont
* @file interfaccesbddbanque.h
* @copyright moi
* @version 1.0
*/
class CompteClient : public QTcpSocket
{
    Q_OBJECT
public:
    CompteClient(QObject *parent=0);

    bool Retirer(float montant);
    void Deposer(float montant);
    float ObtenirSolde();
    int ObtenirNumCompte();
    void DefinirNumCompte(typeClient client);
    bool CompteExite(int _numCompte);
   static  InterfacAccesBDDBanque bd;
private:
   /**
     * @brief numCompte
     * numero de compte
     */
    int numCompte;
    /**
     * @brief solde
     */
    float solde;
};

#endif // COMPTECLIENT_H
