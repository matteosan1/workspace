#include <QCoreApplication>

#include "tdpalioserver.h"

#include <iostream>

int main(int argc, char *argv[]) {

    int a;

    QCoreApplication app(argc, argv);

    if (argc > 1)
        a = atoi(argv[1]);
    else
        a = 1974;

    TDPalioServer* server = new TDPalioServer(a);
    return app.exec();
}
