#include <QCoreApplication>

#include "cloneclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CloneClient();


    return a.exec();
}
