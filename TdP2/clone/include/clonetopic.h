#ifndef CLONETOPIC_H
#define CLONETOPIC_H

#include "utilsclone.h"


/**
 * \brief Internal data structure to hold a topic.
 */
struct CloneTopic {
    quint64 seqn;       ///< Senquence number.
    QUuid uuid;         ///< Uuid of the node who (last) sent this topic.
    QByteArray name;    ///< Name of the topic.
    QByteArray value;   ///< Value of the topic.
    QByteArray props;   ///< Some properties of this topic (may be empty).

    /// Initializes a null object.
    CloneTopic() : seqn(0) {
    }

    /// Returns \c true when the name of the topic is null.
    inline bool isNull() const {
        return name.isNull();
    }

    /**
     * \brief Converts this object to a printable string.
     */
    inline QString toString() const {
        return QString("name %1, seqn %2, uuid %3, %4 and %5")
            .arg(QString(name))
            .arg(seqn)
            .arg(utils::uuid2string(uuid))
            .arg(!value.isEmpty()
                ?  QString("value %1").arg(QString(value.toHex()))
                : "no value")
            .arg(!props.isEmpty()
                ?  QString("props %1").arg(QString(props))
                : "no props");
    }
};

#endif // CLONETOPIC_H
