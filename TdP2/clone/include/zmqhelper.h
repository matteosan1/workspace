#ifndef ZMQHELPER_HPP
#define ZMQHELPER_HPP

#include <QtEndian>
#include <QtGlobal>
#include <QList>
#include <QUuid>

#include <zmq.h>
#include <cerrno>


namespace zmq {

/**
 * \brief Wrapper template function on the \c zmq_setsockopt function.
 */
template<class T>
bool zmqSetsockopt(void *s, int option, T optval)
{
    int rc;

    do {
        rc = zmq_setsockopt(s, option, &optval, sizeof(optval));
    } while (rc == -1 && errno == EINTR);

    return rc == 0;
}

/**
 * \brief Wrapper template function on the \c zmq_getsockopt function.
 */
template<class T>
T zmqGetsockopt(void *s, int option, T defval = 0, bool *ok = 0)
{
    int rc;
    T optval;
    size_t optsize = sizeof(optval);

    do {
        rc = zmq_getsockopt(s, option, &optval, &optsize);
    } while (rc == -1 && errno == EINTR);

    if (ok)
        *ok = rc == 0;

    return rc == 0 ? optval : defval;
}

/**
 * \brief Encodes a ZMQ message part.
 */
///@{
template<class T>
QByteArray zmqEncodeMessagePart(const T &val)
{
    QByteArray ret(sizeof(T), 0);
    qToBigEndian(val, (uchar *) ret.data());
    return ret;
}

template<> inline
QByteArray zmqEncodeMessagePart<QByteArray>(const QByteArray &val)
{
    return val;
}

template<> inline
QByteArray zmqEncodeMessagePart<QUuid>(const QUuid &val)
{
    QByteArray ret(16, 0);
    qToBigEndian<quint32>(val.data1, (uchar *) ret.data());
    qToBigEndian<quint16>(val.data2, (uchar *) ret.data() + 4);
    qToBigEndian<quint16>(val.data3, (uchar *) ret.data() + 6);
    memcpy((uchar *) ret.data() + 8, val.data4, 8);
    return ret;
}
///@}

/**
 * \brief Decodes a ZMQ message part.
 */
///@{
template<class T>
T zmqDecodeMessagePart(const QByteArray &part)
{
    return qFromBigEndian<T>((const uchar *) part.constData());
}

template<> inline
quint8 zmqDecodeMessagePart<quint8>(const QByteArray &part)
{
    if (!part.isEmpty())
        return part[0];
    else
        return 0;
}

template<> inline
QByteArray zmqDecodeMessagePart<QByteArray>(const QByteArray &part)
{
    return part;
}

template<> inline
QUuid zmqDecodeMessagePart<QUuid>(const QByteArray &part)
{
    const quint32 l = qFromBigEndian<quint32>((uchar *) part.constData());
    const quint16 w1 = qFromBigEndian<quint16>((uchar *) part.constData() + 4);
    const quint16 w2 = qFromBigEndian<quint16>((uchar *) part.constData() + 6);
    return QUuid(l, w1, w2, part.at(8), part.at(9), part.at(10),
        part.at(11), part.at(12), part.at(13), part.at(14), part.at(15));
}
///@}

/**
 * \brief Receives an entire ZMQ multipart message.
 *
 * Receives a custom data from a ZMQ socket, without any conversion.
 *
 * \param[in] socket A ZMQ connected socket.
 * \param[in] flags  Flags accepted by function \c zmq_msg_recv.
 *
 * \return The list of ZMQ message parts, as read from the socket.
 *         If data could not be read, an empty list is returned.
 */
QList<QByteArray> zmqRecvMessage(void *socket, int flags = 0);

/**
 * \brief Sends a ZMQ multipart message.
 *
 * Sends a custom data as a ZMQ message, without any conversion.
 *
 * \param[in] socket     A ZMQ connected socket.
 * \param[in] multipart  A multipart message to be sent to the socket.
 * \param[in] flags      Flags accepted by function \c zmq_send.
 *
 * \return \c false in case of any error or \c multipart is empty.
 */
bool zmqSendMessage(void *socket, QList<QByteArray> multipart, int flags = 0);

/**
 * \brief Converts a ZMQ message to a printable hex representation.
 * \param[in] parts A ZMQ message.
 * \return Hex encoded ZMQ message representation.
 */
QByteArray zmqMessageToHex(const QList<QByteArray> &parts);

/**
 * \brief Creates a ZMQ socket.
 *
 * \param[in] context A valid ZMQ context.
 * \param[in] type The type of ZMQ socket to create.
 *
 * \return The newly created ZMQ socket or \c null in case of errors,
 *         e.g. \c context or \c type is not valid.
 */
void *zmqCreateSocket(void *context, int type);

/**
 * \brief Closes the ZMQ socket.
 *
 * Before closing the \c socket, its \c ZMQ_LINGER property is set to 0.
 *
 * \param[in] socket The ZMQ socket to close.
 *
 * \return \c false in case \c socket could not be closed or is invalid.
 */
bool zmqCloseSocket(void *socket);

/**
 * \brief Connects the ZMQ socket.
 *
 * In case of errors, the \c errno variable is set accoring to \c zmq_connect function.
 *
 * \param[in] socket The ZMQ socket to connect.
 * \param[in] endpoint The ZMQ endpoint to use.
 *
 * \return \c false in case \c socket could not be connected.
 */
bool zmqConnectSocket(void *socket, const char *endpoint);

/**
 * \brief Binds the ZMQ socket.
 *
 * In case of errors, the \c errno variable is set accoring to \c zmq_bind function.
 *
 * \param[in] socket The ZMQ socket to bind.
 * \param[in] endpoint The ZMQ endpoint to use.
 *
 * \return \c false in case \c socket could not be bound.
 */
bool zmqBindSocket(void *socket, const char *endpoint);

/**
 * \brief Binds the ZMQ socket, retrying in case of EADDRINUSE error, until timeout.
 *
 * Rebind is done in other to avoid 'address already in use error'
 * when respwaning the same broker, even if SO_REUSEADDR socket option
 * is internally used by ZMQ internals.
 *
 * In case of errors, the \c errno variable is set accoring to \c zmq_bind function.
 *
 * \param[in] socket The ZMQ socket to bind.
 * \param[in] endpoint The ZMQ endpoint to use.
 * \param[in] timeout Timeout in milliseconds until retry is performed
 *                    before returning an error.
 *
 * \return \c false if the \c socket could not be bound to \c endpoint
 *         within \c timeout milliseconds.
 */
bool zmqBindSocketTryReuseaddr(void *socket, const char *endpoint, int timeout);

/**
 * \brief Poll ZMQ sockets.
 *
 * In case of errors, the \c errno variable is set accoring to \c zmq_poll function.
 *
 * \param items List ZMQ sockets.
 * \param nitems Numer of ZMQ sockets.
 * \param msecs Timeout in milliseconds.
 */
bool zmqPoll(zmq_pollitem_t *items, int nitems, long msecs);

/**
 * \brief Subscribes the passed \c socket to the specified \c filter.
 * \param[in] socket A connected ZMQ socket.
 * \param[in] filter A filter to subscribe the socket to.
 * \return \c true in case \c filter was successfully set on the \c socket.
 */
bool zmqSubscribeSocket(void *socket, const QByteArray &filter);

}

#endif // ZMQHELPER_HPP
