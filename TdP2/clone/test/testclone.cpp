#include "clonetestsuite.h"
#include "zlogger.h"

#include <QtTest/QtTest>
#include <QtDebug>
#include <QDir>
#include <QFile>
#include <QUuid>
#include <QList>
#include <QString>
#include <QByteArray>

using namespace logging;

void initZLog()
{
    QDir dir("/tmp");

    QFile zconf(QString("%1/zlog.conf").arg(dir.path()));
    if (!zconf.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QString logfile = "/tmp/test-clone-debug.txt";
    QFile::remove(logfile);

    zconf.write(QString(
        "[global]"                            "\n"
        "default format = \"%d.%ms %V %m%n\"" "\n"

        "[rules]"                             "\n"
        "test.* \"%1\""                       "\n"
        "zmq.* \"%1\""                        "\n"
        "clone.* \"%1\""                      "\n"
    )
    .arg(logfile).toLocal8Bit());

    zconf.close();

    ZLogger::instance()->setConfFile(zconf.fileName());
    ZLogger::instance()->setCategory("test");
}


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    initZLog();

//    QList<QObject *> tests;

//    CloneTestSuite testClone;
//    tests << &testClone;

//    foreach (QObject *test, tests) {
//        if (QTest::qExec(test, app.arguments()) != 0)
//            return 1;
//    }

    CloneTestSuite testClone;
    QTest::qExec(&testClone, app.arguments());

    return 0;
}
