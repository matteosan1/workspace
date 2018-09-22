#ifndef CLONENODEAGENT_H
#define CLONENODEAGENT_H

#include "clonebackend.h"

#include <QElapsedTimer>


class CloneTopic;

/**
 * \brief Commands to communicate with the node agent.
 */
enum NodeAgentCommand {
    Connect = BackendCommand::LAST,
    Disconnect,
    SetSubtree,
    PostTopic,
};


/**
 * \brief This is the class for the main node agent.
 */
class CloneNodeAgent : public CloneBackend
{
    Q_OBJECT

public:
    /**
     * \brief Setups a node agent instance.
     * \param[in] zmqCtx An already initialized ZMQ context.
     * \param[in] uuid Unique identifier to use for this clone node agent (must be non-empty).
     * \param[in] parent Optional \c QObject parent.
     */
    CloneNodeAgent(void *zmqCtx, const QUuid &uuid, QObject *parent = 0);

signals:
    /// \see CloneNodeApp::connectionTimeout
    void connectionTimeout() const;

    /// \see CloneNodeApp::connectionReady
    void connectionReady() const;

    /// \see CloneNodeApp::snapshotSynced
    void snapshotSynced(const QUuid &uuid) const;

    /// \see CloneNodeApp::connectionError
    void connectionError(const QString &endpoint) const;

    /// \see CloneNodeApp::subscriptionError
    void subscriptionError(const QString &topic) const;

    /// \see CloneNodeApp::nodeConnected
    void nodeConnected() const;

    /// \see CloneNodeApp::nodeDisconnected
    void nodeDisconnected() const;

    /// \see CloneNodeApp::topicUpdated
    void topicUpdated(const QByteArray &name, const QByteArray &value, const QUuid &uuid) const;

private:
    /**
     * \brief Dispatches the received request to specific handler functions.
     * \param[in] request A non empty inproc request.
     * \see CloneBackend::handleInprocCommands
     */
    virtual QList<QByteArray> handleInprocCommands(const QList<QByteArray> &request);

    /**
     * \brief Handles a \ref NodeAgentCommand::Connect command and returns back a reply.
     * \param request The CONNECT request.
     * \return \c true in case the command succeeded.
     */
    QList<QByteArray> handleInprocConnect(const QList<QByteArray> &request);

    /**
     * \brief Handles a \ref NodeAgentCommand::Disconnect command and returns back a reply.
     * \param request The DISCONNECT request.
     * \return \c true in case the command succeeded.
     */
    QList<QByteArray> handleInprocDisconnect(const QList<QByteArray> &request);

    /**
     * \brief Handles a ref NodeAgentCommand::Subtree command and returns back a reply.
     *
     * The specified subtrees are not applied until a \ref connectNode operation
     * is performed.
     *
     * \param[in] request The SUBTREE request.
     * \return \c true in case of success.
     */
    QList<QByteArray> handleInprocSetSubtree(const QList<QByteArray> &request);

    /**
     * \brief Handles a ref NodeAgentCommand::PostTopic command and returns back a reply.
     *
     * \param[in] request The POST_TOPIC request.
     * \return \c true in case of success.
     */
    QList<QByteArray> handleInprocPostTopic(const QList<QByteArray> &request);

    /**
     * \brief Connects the node agent to the configured endpoints.
     *
     * In case of successful operations the state machine is reset,
     * otherwise it's halted.
     *
     * \return \c true if the node was successfully connected.
     *
     * \see openSockets
     * \see subscribeNode
     * \see resetStateMachine
     * \see haltStateMachine
     * \see connectionError
     * \see nodeConnected
     */
    bool connectNode();

    /**
     * \brief Opens all the configured sockets.
     *
     * The connection is made using the currently configured endpoints
     * (\ref _epSnapshot, \ref _epUpdate, \ref _epCollector).
     *
     * \return \c false when some socket creation failed.
     *
     * \see connectionError
     * \see CloneBackend::createCommSocket
     */
    bool openSockets();

    /**
     * \brief Disconnects the node agent from the current endpoints.
     *
     * The state of the node agent is set to \ref StateMachine::FsmIdle.
     *
     * \return \c true if the node was successfully disconnected.
     *
     * \see isFsmActive
     * \see closeSockets
     * \see nodeDisconnected
     */
    bool disconnectNode();

    /**
     * \brief Closes all communication sockets.
     * This will possibly cause a communication timeout event,
     * in case the FSM is \ref isFsmActive.
     *
     * \see CloneBackend::deleteCommSocket
     */
    bool closeSockets();

    /**
     * \brief Apply configured \ref _subtrees filters on the \ref _socketUpdate.
     *
     * Subscription is performed every time node is connected.
     * If \ref _subtrees is empty, then \ref _socketUpdate will subscribe to all messages.
     *
     * \see connectNode
     * \see connectionError
     * \see subscriptionError
     */
    bool subscribeNode();

    /**
     * \brief Sends a message to the broker.
     *
     * \param[in] topic Topic of the message.
     * \param[in] value Value of the message.
     * \param[in] enableFilterOutTopic If true, posts only a topic it is subscribed to. Otherwise, posts every topic.
     *
     * \return \c true if the message was successfully sent to the broker.
     */
    bool postTopic(const QByteArray &topic, const QByteArray &value, bool enableFilterOutTopic = false);

    /**
     * \brief Return \c true if \c topic was filtered out.
     * A topic is filtered out when it doesn't match the current \ref _subtrees topics.
     */
    bool filterOutTopic(const QByteArray &topic) const;

    /**
     * \brief Returns whether the node is currently connected or not to the remote server.
     * \return \c true if all the socket are properly connected.
     */
    bool isConnected() const;

    /**
     * \brief Return whether the finite state machine is active.
     * \return \c true when its state is not \ref StateMachine::FsmIdle.
     */
    bool isFsmActive() const;

    /**
     * \brief Performs node agent specific polling on communication sockets.
     */
    void doBackendStep();

    /**
     * \brief Executes the finite state machine.
     */
    void doFsmStep();

    /**
     * \brief Waits for at least one heartbeat or update message to be received.
     */
    void doFsmWaitForHugz();

    /**
     * \brief Send a snapshot request to the server via \ref _socketSnapshot socket.
     */
    void doFsmRequestSnapshot();

    /**
     * \brief Pulls the latest snapshot coming from the remote server via \ref _socketSnapshot socket.
     */
    void doFsmPullSnapshot();

    /**
     * \brief Receives any updates from the server.
     */
    void doFsmListenUpdates();

    /**
     * \brief Resets the finite state machine putting it in \ref StateMachine::FsmRequestSnapshot.
     */
    void resetStateMachine();

    /**
     * \brief Halts the finite state machine putting it in \ref StateMachine::FsmIdle.
     */
    void haltStateMachine();

    /**
     * \brief Parses a KVSYNC reply from server.
     */
    bool parseKvsyncReply(const QList<QByteArray> &reply);

    /**
     * \brief Parses a SNAPSYNC! reply from server.
     */
    bool parseSnapsyncReply(const QList<QByteArray> &reply);

    /**
     * \brief Reads a topic update sent by the broker.
     *
     * \param[out] topic The newly read topic, if available.
     *
     * \return \c true if a new \c topic was successfully received and parsed.
     */
    bool receiveTopic(CloneTopic *topic);

    /**
     * \brief Accepts or rejects a newly received clone topic.
     *
     * A valid topic is rejected if its sequence number is less than the current
     * value of \ref _sequence. Otherwise the topic is accepted, \ref _sequence
     * is updated and the signal \ref topicUpdated is emitted.
     */
    bool acceptTopic(const CloneTopic &topic);

    /**
     * \brief Sends a hugz request to the broker.
     */
    bool sendHugzSync();


private:
    /**
     * \brief Finite State Machine of the node agent.
     */
    enum StateMachine {
        FsmRequestSnapshot,      ///< Request latest remote snapshot.
        FsmPullSnapshot,         ///< Pull latest remote snapshot.
        FsmWaitForHugs,          ///< Wait for pub messages.
        FsmListenUpdates,        ///< Receive updates.
        FsmIdle,                 ///< Idle state.
    };

    StateMachine _nodeFsm;       ///< Finite State Machine of the node.

    QString _epSnapshot;         ///< Endpoint for snapshot socket.
    QString _epCollector;        ///< Endpoint for collector socket.
    QString _epUpdate;           ///< Endpoint for updates socket.
    QList<QByteArray> _subtrees; ///< List of subtrees to subscribe to.

    QElapsedTimer _commTimeout;  ///< Timer to check for communication timeouts.
    QElapsedTimer _hugzSync;     ///< Timer to check for communication timeouts.
    quint64 _sequence;           ///< Current sequence number.
};

#endif // CLONENODEAGENT_H
