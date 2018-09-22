#ifndef CLONEBROKERAGENT_H
#define CLONEBROKERAGENT_H

#include "clonebackend.h"
#include "clonetopic.h"

#include <QString>
#include <QHash>
#include <QElapsedTimer>


/**
 * \brief Commands to communicate with the broker agent.
 */
enum BrokerAgentCommand {
    Bind = BackendCommand::LAST,
    Unbind,
};


/**
 * \brief Class that provides the clone backend.
 */
class CloneBrokerAgent : public CloneBackend
{
    Q_OBJECT

public:
    /**
     * \brief Setups the backend broker agent.
     * \param[in] zmqCtx An already initialized ZMQ context.
     * \param[in] uuid Unique identifier to use for this clone broker agent (must be non-empty).
     * \param[in] parent Optional \c QObject parent.
     */
    CloneBrokerAgent(void *zmqCtx, const QUuid &uuid, QObject *parent = 0);

signals:
    /// \see CloneBrokerApp::snapshotSynced
    void snapshotSynced(const QUuid &uuid) const;

private:
    /**
     * \brief Dispatches the received request to specific handler functions.
     * \param[in] request A non empty inproc request.
     * \see CloneBackend::handleInprocCommands
     */
    virtual QList<QByteArray> handleInprocCommands(const QList<QByteArray> &request);

    /**
     * \brief Handles a \ref BrokerAgentCommand::Bind command and returns back a reply.
     * \param request The BIND request.
     * \return \c true in case the command succeeded.
     */
    QList<QByteArray> handleInprocBind(const QList<QByteArray> &request);

    /**
     * \brief Handles a \ref BrokerAgentCommand::Unbind command and returns back a reply.
     * \param request The UNBIND request.
     * \return \c true in case the command succeeded.
     */
    QList<QByteArray> handleInprocUnbind(const QList<QByteArray> &request);

    /**
     * \brief Returns whether the broker is bound or not.
     */
    bool isBound() const;

    /**
     * \brief Main broker agent communication businnes logic.
     */
    void doBackendStep();

    /**
     * \brief Handles a command received from the snapshot socket.
     */
    void handleSnapshotRequest();

    /**
     * \brief Replies to snapshot requests coming from clients.
     */
    void replyToSnapshotSync(const QByteArray &identity, const QList<QByteArray> &request);

    /**
     * \brief Sends back to the client the specified snapshot topics.
     *
     * Snapshot state is ordered according to their sequence number and only items
     * with sequence number stricly greater than the specified \c sequence are selected.
     *
     * \param[in] identity Identity of the ZMQ requester.
     * \param[in] topics List of topics to send back to the client.
     * \param[in] sequence Only items with sequence number strictly greater than
     *                     this sequence number are sent to the client.
     *
     * \return \c true if the state was successfully sent to the requester.
     */
    bool replyWithSnapshotTopics(const QByteArray &identity, const QList<QByteArray> topics, quint64 sequence) const;

    /**
     * \brief Replies to hugz requests coming from clients.
     */
    void replyToHugzSync(const QByteArray &identity, const QList<QByteArray> &request);

    /**
     * \brief Stores an incoming message to the internal data store.
     * \return The stored topic or a null object otherwise.
     */
    CloneTopic storeTopic();

    /**
     * \brief Creates an heartbeat message ready to be sent.
     */
    CloneTopic makeHugzTopic() const;

    /**
     * \brief Publishes the specified \c topic to other nodes.
     *
     * If the passed \c topic is null, then it's not published.
     * The socket used for publishing is \ref _socketUpdate.
     *
     * \param[in] Topic object to publish.
     */
    void publishTopic(const CloneTopic &topic);

    /**
     * \brief Filters out a \c topic that doesn't match the specified \c filters list.
     *
     * \param[in] topic The topic to check.
     * \param[in] subtrees The filter list.
     *
     * \return \c true if \c topic was filtered out.
     */
    bool filterOutTopic(const QByteArray &topic, const QList<QByteArray> &filters) const;


private:
    quint64 _sequence;                  ///< Sequence number.
    QHash<QString, CloneTopic> _store;  ///< Message store.

    QElapsedTimer _hugzTimeout;         ///< Timeout for heartbeats
};

#endif // CLONEBROKERAGENT_H
