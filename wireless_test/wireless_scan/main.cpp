#include <QCoreApplication>
#include <iwlib.h>

#include <QDebug>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    wireless_scan_head head;
    wireless_scan *result;
    iwrange range;
    int sock;
    char wifi_name[6]={'w','l','p','2','s','0'};

    /* Open socket to kernel */
    sock = iw_sockets_open();

    /* Get some metadata to use for scanning */
    if (iw_get_range_info(sock, wifi_name , &range) < 0)
    {
        qDebug() << "Error during iw_get_range_info. Aborting.";
        return -1;
    }

    /* Perform the scan */
    if (iw_scan(sock, wifi_name, range.we_version_compiled, &head) < 0)
    {
        qDebug() << "Error during iw_scan. Aborting.";
        return -1;
    }

    /* List the resulted network */
    result = head.result;
    qDebug() << "Wireless Feature Test";
    while (NULL != result)
    {
        qDebug() << result->b.essid;
        qint8 level = result->stats.qual.level;
        qDebug() << level;

        result = result->next;
    }
    return 0;


    //return a.exec();
}

