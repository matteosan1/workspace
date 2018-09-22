#ifndef UTILSCLONE_H
#define UTILSCLONE_H

#include <QString>
#include <QUuid>

class CloneNodeApp;
class CloneBrokerApp;


namespace utils {

#define countof(array) (sizeof(array) / sizeof(array[0]))

/**
 * \brief Dynamic assertion evaluated at runtime.
 *
 * This assertion is present in both debug and release code compilations.\n
 * It causes the calling program to abort when the condition expression \c expr
 * evaluates to \c false. It also use the \ref ZLogger facility to print a warning message.
 *
 * \param[in] file Source code file name.
 * \param[in] line Source code line number.
 * \param[in] function Name of the containing function.
 * \param[in] expr Expression to be evaluated.
 * \param[in] assert_message Message to be printed out when assertion fails.
 */
void assertFail(const char *file, unsigned int line, const char *function, const char *expr,
                const char *assert_message);

/**
 * \brief Dynamic assertion evaluated at runtime.
 *
 * This assertion is not stripped away when compiling the base code in release.
 *
 * \see assertFail
 */
#define assert_nomsg(expr) \
    do { \
        if (!(expr)) \
            utils::assertFail(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr, 0); \
    } while (0)

/**
 * \brief Dynamic assertion with message.
 * \see assert_nomsg
 * \see assertFail
 */
#define assert_msg(expr, assert_message) \
    do { \
        if (!(expr)) \
            utils::assertFail(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr, \
                (assert_message)); \
    } while (0)

/**
 * \brief Converts a uuid to a representable and simplified string.
 *
 * E.g the uuid {67C8770B-44F1-410A-AB9A-F9B5446F13EE} is converted to
 * the string "{67C8770B}".
 *
 * Moreover every passed \c uuid is cached to an internal global cache
 * to speed-up the conversion.
 */
QString uuid2string(const QUuid &uuid);

/**
 *  \brief Milliseconds since the system was started, up to 49.7 days
 */
unsigned long long uptime();

/**
 * \brief Helper function to connect a communication node using configuration files.
 * \param ini INI configuration file containing address entries.
 * \param node A valid communication node.
 *
 * \return The same return value fo \ref CloneNodeApp::connectNode.
 *
 * \see addressConfigFile
 * \see CloneNodeApp::connectNode
 */
bool connectCloneNode(const QString &ini, CloneNodeApp *node);

/**
 * \brief Helper function to bind a communication broker using configuration files.
 * \param ini INI configuration file containing address entries.
 * \param broker A valid communication broker.
 *
 * \return The same return value fo \ref CloneBrokerApp::bindBroker
 *
 * \see addressConfigFile
 * \see CloneBrokerApp::bindBroker
 */
bool bindCloneBroker(const QString &ini, CloneBrokerApp *broker);

/**
 * \brief Helper function to post a topic.
 *
 * This function prints and error message in case topic could not be posted,
 * otherwise an informative debug message.
 *
 * \param[in] node A valid node object.
 * \param[in] name Name of topic.
 * \param[in] payload Payload of topic.
 * \return \c false in case of errors.
 * \see CloneNodeApp::postTopic.
 */
bool postCloneTopic(CloneNodeApp *node, const QByteArray &name, const QByteArray &payload);

}

#endif // UTILSCLONE_H
