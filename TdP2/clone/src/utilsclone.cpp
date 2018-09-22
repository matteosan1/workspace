#include "utilsclone.h"
#include "zlogger.h"
#include "clonenodeapp.h"
#include "clonebrokerapp.h"

#include <QSettings>
#include <QStringList>

using namespace logging;

namespace utils {

void assertFail(const char *file, unsigned int line, const char *function, const char *expr,
                const char *assert_message)
{
    zFatal(QString("Assert failure in function %1 (%2 %3): %4%5")
        .arg(function).arg(file).arg(line).arg(expr)
        .arg(assert_message ? QString(": %1").arg(assert_message) : QString()));

    abort();
}

QString uuid2string(const QUuid &uuid)
{
    static QHash<QUuid, QString> cache;

    if (!cache.contains(uuid))
        cache.insert(uuid, QString("{%1}").arg(uuid.toString().mid(1, 8)));

    return cache.value(uuid);
}

unsigned long long uptime()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);

    return static_cast<unsigned long long>(t.tv_sec) * 1000 + t.tv_nsec / 1000000;
}

bool connectCloneNode(const QString &ini, CloneNodeApp *node)
{
    QSettings s(ini, QSettings::IniFormat);

    const QString snap = s.value("NODE/snapshot",  "tcp://127.0.0.1:30001").toString();
    const QString updt = s.value("NODE/update",    "tcp://127.0.0.1:30002").toString();
    const QString coll = s.value("NODE/collector", "tcp://127.0.0.1:30003").toString();

    const bool succ = node->connectNode(snap, updt, coll);

    if (succ)
        zInfo(QString("Node connected to %1, %2, %3")
            .arg(snap).arg(updt).arg(coll));
    else
        zError(QString("Node failed to connect to %1, %2, %3")
            .arg(snap).arg(updt).arg(coll));

    return succ;
}

bool bindCloneBroker(const QString &ini, CloneBrokerApp *broker)
{
    QSettings s(ini, QSettings::IniFormat);

    const QStringList snap(s.value("BROKER/snapshot", "tcp://127.0.0.1:30001").toStringList());
    const QStringList updt(s.value("BROKER/update",   "tcp://127.0.0.1:30002").toStringList());
    const QStringList coll(s.value("BROKER/collector","tcp://127.0.0.1:30003").toStringList());

    const bool succ = broker->bindBroker(snap, updt, coll);

    if (succ)
        zInfo(QString("Broker bound to %1, %2, %3")
            .arg(snap.join(" ")).arg(updt.join(" ")).arg(coll.join(" ")));
    else
        zError(QString("Broker failed to bind to %1, %2, %3")
            .arg(snap.join(" ")).arg(updt.join(" ")).arg(coll.join(" ")));

    return succ;
}

bool postCloneTopic(CloneNodeApp *node, const QByteArray &name, const QByteArray &payload)
{
    // TODO: possibly peform a rate-limited print

    const bool succ = node->postTopic(name, payload);

    if (!succ)
        zWarning(QString("Could not post topic %1")
            .arg(QString(name)));

    return succ;
}

}
