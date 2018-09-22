#include "zmqhelper.h"
#include "zlogger.h"
#include "utilsclone.h"

#include <QString>
#include <QByteArray>
#include <QElapsedTimer>
#include <QThread>

#include <unistd.h>

using namespace logging;

#define zCat(msg) \
    "zmq", msg


namespace {

/**
 * \brief Receives a ZMQ message part.
 *
 * Receives a custom data from a ZMQ socket, without any conversion.\n
 * In case of any error, the global variable \c errno refers to the \c zmq_msg_recv error.
 *
 * \param[in] socket A ZMQ connected socket.
 * \param[out] part  ZMQ part from a multipart message.
 * \param[in] flags  Flags accepted by function \c zmq_msg_recv.
 *
 * \return \c zmq_msg_recv error codes.
 */
int zmqRecvMessagePart(void *socket, QByteArray *part, int flags)
{
    int rc;

    zmq_msg_t msg;
    rc = zmq_msg_init(&msg);
    assert_msg(rc == 0, qPrintable(QString("zmq_msg_init: %1")
        .arg(zmq_strerror(errno))));

    do {
        rc = zmq_msg_recv(&msg, socket, flags);
    } while (rc == -1 && errno == EINTR);

    if (rc == -1 && errno != EAGAIN) {
        zError(zCat(QString("zmq_msg_recv: %1")
            .arg(zmq_strerror(errno))));
    }

    if (rc != -1) {
        part->resize(zmq_msg_size(&msg));
        memcpy(part->data(), zmq_msg_data(&msg), part->size());
    }

    zmq_msg_close(&msg);
    return rc;
}

/**
 * \brief Sends a ZMQ message part.
 *
 * Sends a custom data to a ZMQ socket, without any conversion.\n
 * In case of any error, the global variable \c errno refers to the \c zmq_send error.
 *
 * \param[in] socket A ZMQ connected socket.
 * \param[out] part  ZMQ part of a multipart message.
 * \param[in] flags  Flags accepted by function \c zmq_send.
 *
 * \return \c zmq_send error codes.
 */
int zmqSendMessagePart(void *socket, const QByteArray &part, int flags)
{
    int rc;

    do {
        rc = zmq_send(socket, part.data(), part.size(), flags);
    } while (rc == -1 && errno == EINTR);

    if (rc == -1 && errno != EAGAIN) {
        zError(zCat(QString("zmq_send: %1")
            .arg(zmq_strerror(errno))));
    }

    return rc;
}

}

namespace zmq {

QList<QByteArray> zmqRecvMessage(void *socket, int flags)
{
    QList<QByteArray> multipart;

    for (;;) {
        QByteArray part;
        int rc = zmqRecvMessagePart(socket, &part, flags);
        if (rc == -1)
            return QList<QByteArray>();

        multipart.append(part);

        bool ok;
        int more = zmqGetsockopt<int>(socket, ZMQ_RCVMORE, 0, &ok);

        if (!ok) {
            zError(zCat(QString("zmq_getsockopt: %1")
                .arg(zmq_strerror(errno))));
        }

        if (!more)
            return multipart;
    };
}

QByteArray zmqMessageToHex(const QList<QByteArray> &parts)
{
    QByteArray repr;
    foreach (const QByteArray &p, parts)
        repr.append("[").append(p.toHex()).append("] ");

    return QByteArray("<").append(repr.trimmed()).append(">");
}

bool zmqSendMessage(void *socket, QList<QByteArray> multipart, int flags)
{
    int rc = 0;
    flags &= ZMQ_DONTWAIT;

    if (multipart.isEmpty())
        return false;

    for (int i = 0; i < multipart.size() - 1 && rc != -1; ++i)
        rc = zmqSendMessagePart(socket, multipart.at(i), flags | ZMQ_SNDMORE);

    if (rc != -1)
        rc = zmqSendMessagePart(socket, multipart.last(), flags);

    return rc != -1;
}

void *zmqCreateSocket(void *context, int type)
{
    void *s = zmq_socket(context, type);
    if (!s)
        zError(zCat(QString("zmq_socket: %1")
            .arg(zmq_strerror(errno))));
    return s;
}

bool zmqCloseSocket(void *socket)
{
    if (!socket) {
        zError(zCat(QString("zmq_close: %1").arg(zmq_strerror(ENOTSOCK))));
        return false;
    }

    if (!zmqSetsockopt<int>(socket, ZMQ_LINGER, 0)) {
        zError(zCat(QString("zmq_getsockopt: %1").arg(zmq_strerror(errno))));
        return false;
    }

    if (zmq_close(socket) == -1) {
        zError(zCat(QString("zmq_close: %1").arg(zmq_strerror(errno))));
        return false;
    }

    return true;
}

bool zmqConnectSocket(void *socket, const char *endpoint)
{
    int rc = zmq_connect(socket, endpoint);
    if (rc == -1)
        zError(zCat(QString("zmq_connect: %1").arg(zmq_strerror(errno))));

    return rc == 0;
}

bool zmqBindSocket(void *socket, const char *endpoint)
{
    int rc = zmq_bind(socket, endpoint);
    if (rc == -1)
        zError(zCat(QString("zmq_bind: %1").arg(zmq_strerror(errno))));

    return rc == 0;
}

bool zmqBindSocketTryReuseaddr(void *socket, const char *endpoint, int timeout)
{
    QElapsedTimer t;
    t.start();

    bool bound = false;

    while (t.elapsed() < timeout) {
        /**
         * zmq::zmqBindSocket is not directly used to avoid multiple error messages.
         */
        bound = zmq_bind(socket, endpoint) == 0;

        if (!bound && errno == EADDRINUSE)
            usleep(10000);
        else
            break;
    }

    if (!bound)
        zError(zCat(QString("zmq_bind: %1").arg(zmq_strerror(errno))));

    return bound;
}

bool zmqPoll(zmq_pollitem_t *items, int nitems, long msecs)
{
    int rc;

    do {
        rc = zmq_poll(items, nitems, msecs);
    } while (rc == -1 && errno == EINTR);

    if (rc == -1 && errno != EAGAIN) {
        zError(zCat(QString("zmq_poll: %1").arg(zmq_strerror(errno))));
        return false;
    } else {
        return true;
    }
}

bool zmqSubscribeSocket(void *socket, const QByteArray &filter)
{
    int rc;

    do {
        rc = zmq_setsockopt(socket, ZMQ_SUBSCRIBE, filter.constData(), filter.size());
    } while (rc == -1 && errno == EINTR);

    return rc == 0;
}

}
