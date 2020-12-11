#ifndef BANQUEMAINWINDOW_H
#define BANQUEMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "serveurbanque.h"
/**
* @date 11/12/20
* @author dylan grammont
* @file banquemainwindow.h
* @copyright moi
* @version 1.0
*/

QT_BEGIN_NAMESPACE
namespace Ui { class BanqueMainWindow; }
QT_END_NAMESPACE

class BanqueMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BanqueMainWindow(QWidget *parent = nullptr);
    ~BanqueMainWindow();

private:
    /**
     * @brief ui
     */
    Ui::BanqueMainWindow *ui;
    /**
     * @brief leServeur
     */
    ServeurBanque *leServeur;
};
#endif // BANQUEMAINWINDOW_H
