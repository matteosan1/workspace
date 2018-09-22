#include "testutils.h"

#include <QCoreApplication>
#include <QString>
#include <QTemporaryFile>
#include <QFile>
#include <QThread>
#include <QObject>
#include <QTest>
#include <QSignalSpy>
#include <QTextStream>

#include "zlogger.h"

using namespace logging;

#define SOCK_SNAP_ADDR  "ipc:///tmp/_sock_clone_snap"
#define SOCK_UPDT_ADDR  "ipc:///tmp/_sock_clone_updt"
#define SOCK_COLL_ADDR  "ipc:///tmp/_sock_clone_coll"

namespace test {
namespace utils {

QTemporaryFile *createZLogConfigFile(const QString& testName,
                                     const QStringList& logList,
                                     const QStringList& dropList)
{
    QTemporaryFile *conf = new QTemporaryFile();

    QString logfile = "/tmp/test-" + testName + "-debug.txt";
    QFile::remove(logfile);

    QByteArray content("[global]\n"
                       "default format = \"%d.%ms %V %m%n\"\n\n"
                       "[rules]\n");

    foreach (QString module, logList) {
        content.append(module).append(".* \"").append(logfile).append("\"\n");
    }

    foreach (QString module, dropList) {
        content.append(module).append(".* \"/dev/null\"\n");
    }

    conf->open();
    conf->write(content);
    conf->close();

    return conf;
}


QTemporaryFile *createAddressConfigFile()
{
    QTemporaryFile *conf = new QTemporaryFile();

    conf->open();
    conf->write(QString("[BROKER]\n"
                        "snapshot=%1\n"
                        "update=%2\n"
                        "collector=%3\n\n"
                        "[NODE]\n"
                        "snapshot=%1\n"
                        "update=%2\n"
                        "collector=%3\n")
                .arg(SOCK_SNAP_ADDR)
                .arg(SOCK_UPDT_ADDR)
                .arg(SOCK_COLL_ADDR)
                .toLocal8Bit());
    conf->close();

    return conf;
}


QTemporaryFile *createModuleConfigFile(const QTemporaryFile *zlogFile,
                                       const QTemporaryFile *addrFile,
                                       const QString& customContent)
{
    QTemporaryFile *conf = new QTemporaryFile();

    conf->open();
    conf->write(QString("[addr]\n"
                        "file=%1\n\n"
                        "[zlog]\n"
                        "file=%2\n")
                .arg(zlogFile->fileName())
                .arg(addrFile->fileName())
                .append(customContent)
                .toLocal8Bit());
    conf->close();

    return conf;
}


void configureTestApplication(QCoreApplication &app,
                              const QTemporaryFile *zlogFile,
                              const QTemporaryFile *addrFile,
                              const QTemporaryFile *moduleFile,
                              const QString &cat)
{
    app.setProperty("configfile", moduleFile->fileName());
    app.setProperty("addressfile", addrFile->fileName());

    ZLogger::instance()->setConfFile(zlogFile->fileName());
    ZLogger::instance()->setCategory(cat);
}


bool waitForSignal(QObject *obj, const char *signal, int timeoutMsec,
    int count, QList<QList<QVariant>> args, const char *until)
{
    QElapsedTimer timer;
    timer.start();

    QSignalSpy spy(obj, signal);
    QSignalSpy *utl = 0;
    if (until)
        utl = new QSignalSpy(obj, until);

    QCoreApplication::processEvents(QEventLoop::AllEvents);

    while (((!utl && spy.count() < count) || (utl && utl->count() == 0))
        && timer.elapsed() < timeoutMsec)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents);
        QTest::qWait(1);
    }

    if (utl) {
        bool ok = utl->count() != 0;
        delete utl;
        if (!ok) {
            QWARN(qPrintable(QString("Signal %1 not emitted").arg(until)));
            return false;
        }
    }

    // FIXME: Disable arguments to avoid failures on QT 4.8
//    if (spy.count() != count) {
//        QWARN(qPrintable(QString("Signal count mismatch: "
//            "expected '%1', actual '%2'")
//            .arg(count)
//            .arg(spy.count())
//        ));
//        return false;
//    }

//    for (int i = 0; i < spy.count() && i < args.size(); ++i) {
//        QList<QVariant> spyargs = spy.at(i);
//        QList<QVariant> testargs = args.at(i);
//        if (spyargs.size() != testargs.size()) {
//            QWARN(qPrintable(QString("Signal arguments number mismatch: "
//                "expected '%1', actual '%2'")
//                .arg(testargs.size())
//                .arg(spyargs.size())
//            ));
//            return false;
//        }

//        for (int j = 0; j < spyargs.size(); ++j) {
//            if (spyargs.at(j) != testargs.at(j)) {
//                QWARN(qPrintable(QString("Signal arguments values mismatch: "
//                    "expected '%1', actual '%2'")
//                    .arg(testargs.at(j).toString())
//                    .arg(spyargs.at(j).toString())
//                ));
//                return false;
//            }
//        }
//    }

    return true;
}


int countSignals(QObject *obj, const char *signal)
{
    QSignalSpy spy(obj, signal);
    QCoreApplication::processEvents(QEventLoop::AllEvents);
    return spy.count();
}

bool catchSignal(QObject *obj, const char *signal, int timeoutMsec,
    std::function<bool (const QList<QVariant> &)> validate)
{
    QElapsedTimer timer;
    timer.start();

    int lastIdx = 0;
    QSignalSpy spy(obj, signal);

    while (1) {
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        while (lastIdx < spy.count()) {
            if (validate(spy.at(lastIdx++)))
                return true;
        }

        if (timer.elapsed() >= timeoutMsec)
            break;

        QTest::qWait(1);
    }

    return false;
}

bool writeFile(const QString &filename, const QStringList &lines)
{
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QWARN(qPrintable(QString("Could not create file %1").arg(file.fileName())));
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");

    foreach (const QString &line, lines)
        out << line << "\n";

    return true;
}

}   // end of namespace utils
}   // end of namespace test
