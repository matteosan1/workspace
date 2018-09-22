#ifndef CLONENODEAPP_H
#define CLONENODEAPP_H

#include "clonefrontend.h"


/**
 * \brier Class which represents a generic clone node.
 *
 * This class is not thread safe.
 */
class CloneNodeApp : public CloneFrontend
{
    Q_OBJECT

public:
    /**
     * \brief Creates and starts a new clone instance.
     * \param[in] parent Optional parent object.
     * \return A new clone instance.
     */
    static CloneNodeApp * createNode(QObject *parent = 0);


signals:
    /**
     * \brief Signal emitted when the node was connected to the remote broker.
     *
     * After connection, signal \ref connectionReady is emitted to notify that
     * communication channels are ready to be used, otherwise \ref connectionTimeout
     * is emitted in case broker was not detected.
     *
     * \see connectNode
     * \see connectionReady
     * \see connectionTimeout
     */
    void nodeConnected() const;

    /**
     * \brief Signal emitted when the node was disconnected from the remote broker.
     * \see disconnectNode
     */
    void nodeDisconnected() const;

    /**
     * \brief Signal emitted when the node could not be connected.
     * \param endpoint Address that caused the error.
     */
    void connectionError(const QString &endpoint) const;

    /**
     * \brief Signal emitted when the node could not subscribe to a \c topic.
     * \param topic Topic that caused the error (a null string means 'no filter').
     */
    void subscriptionError(const QString &topic) const;

    /**
     * \brief Signal emitted when lack of communication is detected.
     *
     * This event happens after having connected the node to the remote broker,
     * in case the connection timeout has expired. Thus some messages may be lost
     * due to communication issues but, after automatic reconnection, the latest
     * available snapshot will be synced again.
     *
     * \see nodeConnected
     * \see snapshotSynced
     */
    void connectionTimeout() const;

    /**
     * \brief Signal emitted when communication channels are ready to be used.
     *
     * This event happens after connecting the node to the remote broker,
     * because the publisher-subscriber socket takes a little amount of time
     * before being ready to be used.
     *
     * \see nodeConnected
     */
    void connectionReady() const;

    /**
     * \brief Signal emitted when state snapshot was successfully synced with remote master.
     * \param uuid Broker node identifier.
     * \see topicUpdated
     */
    void snapshotSynced(const QUuid &uuid) const;

    /**
     * \brief Signal emitted when a topic has been updated by this node or other nodes.
     *
     * A topic update is emitted because of a \ref postTopic call by this or other nodes,
     * or because of the sync of the remote broker's state.
     *
     * \param name Name of the topic.
     * \param value Value of the topic.
     * \param uuid The node/broker who triggered this update.
     */
    void topicUpdated(const QByteArray &name, const QByteArray &value, const QUuid &uuid) const;


public slots:
    /**
     * \brief Connects the node to the specified server.
     *
     * After connecting the node to the remote broker, the node first tries to synchronize
     * its state with remote broker's (\ref snapshotSynced), causing some \ref topicUpdated
     * signals to be emitted.
     *
     * After that, node waits for its publisher-subscriber socket to be ready to be used
     * (\ref connectionReady). Using \ref postTopic before \ref connectionReady may lead
     * to the lack of \ref topicUpdated acknoweledgement.
     *
     * Finally, the node enters the final stage such that the status of connection
     * is monitored, then in case of connection error signal \ref connectionTimeout
     * is emitted and the node begins the connection procedure.
     *
     * \param snapshot Endpoint to connect the snapshot socket to.
     * \param updates Endpoint to connect the updates socket to.
     * \param collector Endpoint to connect the collector socket to.
     *
     * \return \c true if the node was successfully connected to the specified endpoints.
     *
     * \see nodeConnected
     * \see connectionReady
     * \see connectionTimeout
     */
    bool connectNode(const QString &snapshot, const QString &update,
        const QString &collector);

    /**
     * \brief Disconnects the node from the clone network.
     */
    bool disconnectNode();

    /**
     * \brief Set the list of topics the node is subscribed to.
     *
     * The node is actually subscribed to the specified list of \c topics
     * as soon as the node is connected to the server, by means of \ref connectNode
     * or because of a connection timeout, if already connected.
     *
     * The specified list of \c topics is a filter for both sent and received messages.
     *
     * \param[in] topics List of subscription sockets.
     *                   Both the list and its items must be non-emtpy.
     *
     * \return \c true in case \c topics are successfully configured for next connection.
     *
     * \see subscribeToAllTopics
     */
    bool subscribeToSpecificTopics(const QList<QByteArray> &topics);

    /**
     * \brief Removes any filter on sent and received topics.
     * This causes the node to be subscribed to all messages.
     * \see subscribeToSpecificTopics
     */
    bool subscribeToAllTopics();

    /**
     * \brief Posts a topic to other nodes.
     *
     * The topic is just forwarded to all subscribed nodes.
     * In order to make it persistent, its \c name must starts with \c "/state".
     * For every post, a signal \ref topicUpdate is emitted,
     * even respect to the node who submitted this update.
     *
     * \param[in] name A custom name of the topic, without any restrictions.
     *                 If name starts with \c "/state", then the topic
     *                 is considered as persistent and thus it's saved.
     *
     * \param[in] value A custom value of the topic.
     *
     * \return \c true if the topic was successfully posted.
     *
     * \see topicUpdated
     * \see connectionReady
     * \see snapshotSynced
     */
    bool postTopic(const QByteArray &name, const QByteArray &value);


private:
    /**
     * \brief Setups a node instance and starts a \ref CloneNodeAgent in a separate thread.
     * \param[in] parent Optional \c QObject parent.
     */
    CloneNodeApp(QObject *parent = 0);
};

#endif // CLONENODEAPP_H
