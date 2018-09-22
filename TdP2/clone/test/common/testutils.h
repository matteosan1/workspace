#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QList>
#include <QVariant>

#include <functional>


// forward declarations
class QTemporaryDir;
class QTemporaryFile;
class QCoreApplication;
class QString;
class QStringList;
class QObject;


namespace test {
namespace utils {

/**
 * \brief Creates a temporary config file for the zlog component.
 *
 * The caller will acquire the ownership of the returned object and will be
 * responsible for its deletion.
 *
 * \param testName  Name of the module being tested (the output log file will
 *                  be /tmp/test-<testName>-debug.txt).
 * \param logList   List of module names to be logged.
 * \param dropList  List of module names to be silenced.
 * \return A pointer to a QTemporaryFile object abstracting the temporary
 *         config file.
 */
QTemporaryFile *createZLogConfigFile(const QString& testName,
                                     const QStringList& logList,
                                     const QStringList& dropList);

/**
 * \brief Creates a temporary config file containing the adresses of the broker
 *        and the nodes.
 *
 * The caller will acquire the ownership of the returned object and will be
 * responsible for its deletion.
 *
 * \return A pointer to a QTemporaryFile object abstracting the temporary
 *         config file.
 */
QTemporaryFile *createAddressConfigFile();

/**
 * \brief Creates a temporary config file for a generic module, containing
 *        the path to the zlog config file and the path to the addresses
 *        config file.
 *
 * The caller will acquire the ownership of the returned object and will be
 * responsible for its deletion. The function can be extended to add more
 * information to the module config file.

 * \param zlogFile      Object that abstracts the zlog config file.
 * \param addrFile      Object that abstracts the addresses config file.
 * \param customContent Additional content that will be written after the
 *                      sections addr and zlog.
 * \return A pointer to a QTemporaryFile object abstracting the temporary
 *         config file.
 */
QTemporaryFile *createModuleConfigFile(const QTemporaryFile *zlogFile,
                                       const QTemporaryFile *addrFile,
                                       const QString& customContent = QString());

/**
 * \brief Configures the test application, setting the properties storing the
 *        paths to the config files; it also initializes the zlogger component.
 * \param app           Reference to the QCoreApplication object.
 * \param zlogFile      Object that abstracts the zlog config file.
 * \param addrFile      Object that abstracts the addresses config file.
 * \param moduleFile    Object that abstracts the module config file.
 * \param cat           String representing the category assigned to the log
 *                      messages.
 */
void configureTestApplication(QCoreApplication &app,
                              const QTemporaryFile *zlogFile,
                              const QTemporaryFile *addrFile,
                              const QTemporaryFile *moduleFile,
                              const QString &cat);

/**
 * \brief Waits for the given signal to be emitted by the given object.
 *
 * Returns after timeoutMsec milliseconds, or after a number of signals of the
 * given type equal to count has been emitted, or as soon as another signal
 * identified by the until parameter has been emitted. It can also check the
 * validity of the arguments of the received signals.
 *
 * \param obj           Emitter of the signals.
 * \param signal        Type of the main signal we are interested in.
 * \param timeoutMsec   Maximum wait time in milliseconds.
 * \param count         Number of signals to wait for.
 * \param args          Expected signal arguments.
 * \param until         Next signal type, after count signals of type signal.
 * \return
 */
bool waitForSignal(QObject *obj, const char *signal, int timeoutMsec, int count = 1,
                   QList<QList<QVariant>> args = QList<QList<QVariant>>(),
                   const char *until = 0);

/**
 * \brief Returns the number of signals of the given type emitted by the given
 *        object.
 * \param obj       Emitter of the signal.
 * \param signal    Signal to be observed.
 * \return The number of signals of the given type emitted by the given object.
 */
int countSignals(QObject *obj, const char *signal);

/**
 * \brief Catches a signal, if emitted until the specified timeout.
 * \param[in] obj Emitter of the signal.
 * \param[in] signal Signal to catch.
 * \param[in] timeoutMsec Timeout in milliseconds to wait for the signal.
 * \param[in] validate Validation function to catch signal.
 * \return \c false if no signals matched the \c validate function.
 */
bool catchSignal(QObject *obj, const char *signal, int timeoutMsec,
    std::function<bool (const QList<QVariant> &)> validate);

/**
 * \brief Writes a file in the specified directory.
 * \param[in] filename Name and path of file.
 * \param[in] lines Content of file.
 * \return \c false in case file could not be written.
 */
bool writeFile(const QString &filename, const QStringList &lines);

}   // end namespace utils
}   // end namespace test

#endif  // TESTUTILS_H
