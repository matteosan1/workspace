#ifndef CLONEBACKEND_H
#define CLONEBACKEND_H

#include <QObject>
#include <QString>
#include <QUuid>

#include <functional>


/**
 * \brief Commands to communicate with the node agent.
 */
enum BackendCommand {
    Stop = 1,
    LAST,
};

typedef quint8 backend_cmd_t;
typedef quint8 backend_ret_t;


/**
 * \brief This is the class for the main backend.
 */
class CloneBackend : public QObject
{
    Q_OBJECT

public:
    /**
     * \brief Setups a backend instance.
     * \param[in] zmqCtx An already initialized ZMQ context.
     * \param[in] uuid Unique identifier to use for this clone node agent (must be non-empty).
     * \param[in] parent Optional \c QObject parent.
     */
    CloneBackend(const QString &name, void *zmqCtx, const QUuid &uuid, QObject *parent = 0);

    /**
     * \brief Destroys this instance of clone backend.
     */
    virtual ~CloneBackend();

public slots:
    /**
     * \brief Runs the main backend routine for a maximum time of \c msecs milliseconds.
     *
     * \param[in] msecs Maximum time (in milliseconds) to run the node agent routing for.\n
     *            If \c msecs is -1, this function will not time out.
     */
    void doWork(int msecs = -1);

signals:
    /**
     * \brief Emitted when this backend has started its \ref doWork routine.
     */
    void started() const;

    /**
     * \brief Emitted when this backend has finished its \ref doWork routine.
     */
    void finished() const;

protected:
    /**
     * \brief Performs backend-specific polling and logic on communication sockets.
     *
     * This function must be non-blocking since it is executed for every loop cycle
     * from within the \ref doWork main routine.
     *
     * \see doWork
     */
    virtual void doBackendStep();

    /**
     * \brief Creates a ZMQ socket used for communication with other close backends.
     * \param[out] socket The newly created socket.
     * \param[in] type The type of socket to be created.
     * \param[in] connectSocket Function that connects or binds the \c socket
     *            one of \ref zmq::zmqConnectSocket or \ref zmq::zmqBindSocket.
     * \param[in] endpoints List of endpoints to connect the socket to.
     * \param[in] descr A printable description of the socket.
     * \return \c true if the socket was successfully created and connected.
     */
    bool createCommSocket(void * &socket, int type,
        std::function<bool (void *, const char *)> connectSocket,
        const QList<QString> &endpoints, const QString &descr);

    /**
     * \brief Deletes a ZMQ socket used for communication with other clone backends.
     * \param[out] socket The socket to be destroyed (its pointer is set to \c null).
     * \param[in] descr A printable description of the socket.
     */
    bool deleteCommSocket(void * &socket, const QString &descr);

    /**
     * \brief Polls the specified \c socket for a time of \c msecs milliseconds.
     *
     * \param[in] socket ZMQ socket to poll.
     * \param[in] msecs Timeout in milliseconds for the poll function.
     *
     * \return \c true if the socket is readable.
     *
     * \see zmq::zmqPoll
     */
    bool isSocketReadable(void * socket, int msecs = 1) const;

    /**
     * \brief Receives an inproc command from the clone frontend and sends a reply back.
     *
     * The socket used for inproc communication is \ref _socketInproc.
     */
    void handleInprocCommands();

    /**
     * \brief Dispatches the received request to specific handler functions.
     * \param[in] request A non empty inproc request.
     */
    virtual QList<QByteArray> handleInprocCommands(const QList<QByteArray> &request);

    /**
     * \brief Handles a specific inproc command from clone frontend.
     * \param cmdstr The printable name of the command.
     * \param cmdfun The function which handles the specific command.
     * \return The reply to the inproc command to be sent back (non empty).
     */
    QList<QByteArray> handleInprocCommand(const QString &cmdstr,
        std::function<QList<QByteArray> (const QList<QByteArray> &)> cmdfun,
        const QList<QByteArray> &request);

    /**
     * \brief Handles an unknown command request.
     * \param request The unknown request (not used, actually).
     * \return \c false.
     */
    QList<QByteArray> handleInprocUnknown(const QList<QByteArray> &request);

    /**
     * \brief Handles a \ref BackendCommand::STOP command and returns back a reply.
     * \param request The STOP request.
     * \return \c true.
     */
    QList<QByteArray> handleInprocStop(const QList<QByteArray> &request);


protected:
    void *_zmqCtx;          ///< ZMQ context.
    const QUuid _uuid;      ///< Node unique identifier.
    const QString _name;    ///< Name of this clone backend.

    void *_socketInproc;    ///< ZMQ socket connected to the node.
    void *_socketSnapshot;  ///< ZMQ socket connected to the snapshot endpoint.
    void *_socketUpdate;    ///< ZMQ socket connected to the update endpoint.
    void *_socketCollector; ///< ZMQ socket connected to the collector endpoint.

    bool _stopped;          ///< Whether the node agent has been stopped.
};

#endif // CLONEBACKEND_H
