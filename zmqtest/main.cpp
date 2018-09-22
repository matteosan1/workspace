#include <QCoreApplication>

#include "mysocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MySocket s;

    return a.exec();
}
