#include "banquemainwindow.h"
#include "ui_banquemainwindow.h"
/**
* @date 11/12/20
* @author dylan grammont
* @file banquemainwindow.cpp
* @copyright moi
* @version 1.0
*/

/**
 * @brief BanqueMainWindow::BanqueMainWindow
 * @param parent
 * constructeur de la classe BanqueMainWindow
 */
BanqueMainWindow::BanqueMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BanqueMainWindow)
    ,leServeur (new ServeurBanque)
{
    ui->setupUi(this);
   leServeur->Start();

}
/**
 * @brief BanqueMainWindow::~BanqueMainWindow
 * destructeur de la classe BanqueMainWindow
 */
BanqueMainWindow::~BanqueMainWindow()
{
    delete ui;
    leServeur->Stop();
    delete  leServeur;
}

