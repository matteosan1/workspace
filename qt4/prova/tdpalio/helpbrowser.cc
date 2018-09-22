/*

#include <qapplication.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <q3textbrowser.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3HBoxLayout>
#include "helpbrowser.h"

HelpBrowser::HelpBrowser(const QString &path, const QString &page,
                          QWidget *parent, const char *name)
    : QWidget(parent, name, Qt::WGroupLeader | Qt::WDestructiveClose)
{
    textBrowser = new Q3TextBrowser(this);
    homeButton = new QPushButton(tr("&Home"), this);
    backButton = new QPushButton(tr("&Back"), this);
    closeButton = new QPushButton(tr("Close"), this);
    closeButton->setAccel(tr("Esc"));
    Q3VBoxLayout *mainLayout = new Q3VBoxLayout(this);
    Q3HBoxLayout *buttonLayout = new Q3HBoxLayout(mainLayout);
    buttonLayout->addWidget(homeButton);
    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(closeButton);
    mainLayout->addWidget(textBrowser);
    connect(homeButton, SIGNAL(clicked()),
            textBrowser, SLOT(home()));
    connect(backButton, SIGNAL(clicked()),
            textBrowser, SLOT(backward()));
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(textBrowser, SIGNAL(sourceChanged(const QString &)),
            this, SLOT(updateCaption()));

  textBrowser->mimeSourceFactory()->addFilePath(path);
  textBrowser->setSource(page);
}

void HelpBrowser::updateCaption() {
    setCaption(tr("Help: %1").arg(textBrowser->documentTitle()));
}

void HelpBrowser::showPage(const QString &page) {
    QString path = qApp->applicationDirPath() + "/doc";
    HelpBrowser *browser = new HelpBrowser(path, page);
    browser->resize(500, 400);
    browser->show();
}

*/
