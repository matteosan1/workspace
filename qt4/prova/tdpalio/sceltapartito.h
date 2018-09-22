/*
#ifndef SCELTAPARTITO_H
#define SCELTAPARTITO_H

#include <qvariant.h>
#include <qdialog.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class QLabel;
class QComboBox;
class QSpinBox;
class Q3ButtonGroup;
class QRadioButton;
class QPushButton;

class SceltaPartito : public QDialog
{
    Q_OBJECT

public:
    SceltaPartito( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~SceltaPartito();

    QLabel* playerLabel;
    QLabel* contLabel;
    QComboBox* comboContrade;
    QLabel* offertaLabel;
    QSpinBox* spinBox1;
    Q3ButtonGroup* partitiGroup;
    QRadioButton* tipo1;
    QRadioButton* tipo3;
    QRadioButton* tipo2;
    QComboBox* comboContrade2;
    QPushButton* okButton;
    QPushButton* cancelButton;

    virtual int Chi();
    virtual int Tipo();
    virtual int ControChi();
    virtual int Offerta();

public slots:
    virtual void FillCombo( QString a, QStringList q );
    virtual void enableCombo( bool a );

protected:
    Q3VBoxLayout* SceltaPartitoLayout;
    Q3VBoxLayout* layout6;
    QSpacerItem* spacer11;
    QSpacerItem* spacer5;
    Q3HBoxLayout* layout5;
    QSpacerItem* spacer10_2;
    QSpacerItem* spacer9_2;
    Q3HBoxLayout* layout10;
    QSpacerItem* spacer7;
    Q3VBoxLayout* layout8;
    QSpacerItem* spacer9;
    QSpacerItem* spacer10;
    QSpacerItem* spacer8;
    Q3HBoxLayout* layout4;
    QSpacerItem* spacer2;
    QSpacerItem* spacer1;
    QSpacerItem* spacer3;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // SCELTAPARTITO_H
*/
