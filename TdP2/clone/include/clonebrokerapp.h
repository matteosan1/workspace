#ifndef CLONEBROKERAPP_H
#define CLONEBROKERAPP_H

#include "clonefrontend.h"

/**
 * \brief Class which represents the broker part of the Clone Pattern.
 */
class CloneBrokerApp : public CloneFrontend
{
    Q_OBJECT


public:
    /**
     * \brief Creates and starts a new broker instance.
     * \param[in] parent Optional parent object.
     * \return A new broker instance.
     */
    static CloneBrokerApp * createBroker(QObject *parent = 0);


public slots:
    /**
     * \brief Binds this broker to the specified enpoints.
     * \param[in] snapshot List of enpoints for the snapshot socket.
     * \param[in] update List of enpoints for the update socket.
     * \param[in] collector List of enpoints for the collector socket.
     * \return \c true if every socket could be bound to its endpoints,
     *         \c false otherwise.
     */
    bool bindBroker(const QList<QString> &snapshot, const QList<QString> &update,
        const QList<QString> &collector);

    /**
     * \brief Unbinds this broker from the clone network.
     */
    bool unbindBroker();

signals:
    /**
     * \brief Signal emitted when current snapshot was successfully synced with a node.
     * \param uuid Node uuid the snapshot was synced with.
     */
    void snapshotSynced(const QUuid &uuid) const;


private:
    /**
     * \brief Setups a broker instance and starts a \ref CloneBrokerAgent in a separate thread.
     * \param[in] parent Optional \c QObject parent.
     */
    CloneBrokerApp(QObject *parent = 0);
};

#endif // CLONEBROKER_H
