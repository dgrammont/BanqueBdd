#include "banquemainwindow.h"

#include <QApplication>

/**
* @date 11/12/20
* @author dylan grammont
* @file main.cpp
* @copyright moi
* @version 1.0
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BanqueMainWindow w;
    w.show();
    return a.exec();
}
