#ifndef CLONEFRONTEND_H
#define CLONEFRONTEND_H

#include <QObject>
#include <QString>
#include <QUuid>

#include <functional>


class CloneBackend;
class QThread;

/**
 * \brier Class which represents a generic clone frontend to a specific clone backend.
 *
 * This class is not thread safe.
 */
class CloneFrontend : public QObject
{
    Q_OBJECT

public:
    /**
     * \brief Requests the \ref CloneBackend to stop and waits for its termination.
     */
    virtual ~CloneFrontend();

    /**
     * \brief Returns the unique identifier of this clone node.
     */
    QUuid uuid() const;


protected:
    typedef std::function<CloneBackend *(void *, const QUuid &)> make_backend_t;

    /**
     * \brief Setups a node instance and starts a \ref CloneBackend in a separate thread.
     * \param[in] name Printable description of this backend.
     * \param[in] createBackend Factory method to create a specific instance of a backend.
     * \param[in] parent Optional \c QObject parent.
     */
    CloneFrontend(const QString &name, make_backend_t createBackend, QObject *parent = 0);

    /**
     * \brief Starts the clone backend.
     *
     * The backend routine is executed for a maximum time of \c msecs milliseconds.
     *
     * \param[in] msecs Maximum time (in milliseconds) to run the backend for.\n
     *                  If \c msecs is -1, the backend will not time out.
     */
    void startBackend(int msecs = -1);

    /**
     * \brief Stops the currently running backend.
     */
    void stopBackend();

    /**
     * \brief Creates the ZMQ inproc socket.
     * \see deleteInprocSocket
     */
    void createInprocSocket();

    /**
     * \brief Deletes the ZMQ inproc socket.
     * \see createInprocSocket
     */
    void deleteInprocSocket();

    /**
     * \brief Generic template handler for inproc node agent commands.
     * \param[in] cmdstr Printable command name.
     * \param[in] request Complete command parts to be sent.
     * \param[in] handleReply Function that handles the node agent's reply.
     * \return \c true if no errors occurred.
     */
    bool handleInprocCommand(const QString &cmdstr, const QList<QByteArray> request,
        std::function<bool (const QList<QByteArray> &)> handleReply =
            [](const QList<QByteArray> &) {
                return true;
            }
    );


protected:
    void *const _zmqCtx;               ///< ZMQ context.
    const QUuid _uuid;                 ///< UUID of this node.
    const QString _name;               ///< Name of this clone frontend.

    QThread *const _cloneThread;       ///< Thread that runs the node agent.
    CloneBackend *const _cloneBackend; ///< Actual clone node agent object.

    void *_socketInproc;               ///< ZMQ Socket connected to the node agent.
};

#endif // CLONEFRONTEND_H
