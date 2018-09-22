#include <QApplication>
#include <QtSql>

#include <QList>
#include <QString>
#include <QImage>

#include <QDebug>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
