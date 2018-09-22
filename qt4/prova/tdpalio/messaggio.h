/*
#ifndef MESSAGGIO_H
#define MESSAGGIO_H

#include <qvariant.h>
#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class Q3ListView;
class Q3ListViewItem;

class Messaggio : public QDialog {
    Q_OBJECT

public:
    Messaggio( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~Messaggio();

    QLabel* contradaLabel;
    QLabel* capitanoLabel;
    QPushButton* leggiButton;
    Q3ListView* messaggiList;
    QPushButton* okButton;

public slots:
    virtual void InserisciMessaggio( QString mex, bool check );

protected:
    Q3VBoxLayout* MessaggioLayout;
    Q3VBoxLayout* layout86;
    Q3VBoxLayout* layout84;
    Q3HBoxLayout* layout83;
    QSpacerItem* spacer22;
    QSpacerItem* spacer22_2;
    Q3VBoxLayout* layout81;
    Q3HBoxLayout* layout85;
    QSpacerItem* spacer24;
    QSpacerItem* spacer25;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // MESSAGGIO_H
*/