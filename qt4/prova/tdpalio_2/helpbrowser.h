#ifndef HELP_H
#define HELP_H

#include <qwidget.h>

class QPushButton;
class QTextBrowser;
class HelpBrowser : public QWidget {
    Q_OBJECT
public:
    HelpBrowser(const QString &path, const QString &page,
                QWidget *parent = 0, const char *name = 0);
    static void showPage(const QString &page);
private slots:
    void updateCaption();
private:
   QTextBrowser *textBrowser;
   QPushButton *homeButton;
   QPushButton *backButton;
   QPushButton *closeButton;
};
#endif
