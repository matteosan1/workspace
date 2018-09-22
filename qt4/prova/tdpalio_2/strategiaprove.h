/****************************************************************************
** Form interface generated from reading ui file 'strategiaprove.ui'
**
** Created: Fri Oct 12 19:43:44 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef STRATEGIAPROVE_H
#define STRATEGIAPROVE_H

#include <qvariant.h>
#include <qdialog.h>
#include "barbero.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QGroupBox;
class QComboBox;
class QCheckBox;
class QSpinBox;
class QProgressBar;
class QPushButton;

class StrategiaProve : public QDialog
{
    Q_OBJECT

public:
    StrategiaProve( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~StrategiaProve();

    QLabel* contradaLabel;
    QLabel* montaLabel;
    QGroupBox* scelta1Box;
    QComboBox* scelta1Combo;
    QCheckBox* scelta1Check;
    QComboBox* contrada1Combo;
    QSpinBox* scelta1Spin;
    QGroupBox* scelta2Group;
    QComboBox* scelta2Combo;
    QCheckBox* scelta2Check;
    QSpinBox* scelta2Spin;
    QComboBox* contrada2Combo;
    QGroupBox* scelta3Group;
    QComboBox* scelta3Combo;
    QCheckBox* scelta3Check;
    QSpinBox* scelta3Spin;
    QComboBox* contrada3Combo;
    QGroupBox* provaBox;
    QLabel* primaLabel;
    QLabel* secondaLabel;
    QLabel* terzaLabel;
    QLabel* quartaLabel;
    QLabel* generaleLabel;
    QLabel* acciaLabel;
    QComboBox* primaCombo;
    QComboBox* secondaCombo;
    QComboBox* terzaCombo;
    QComboBox* quartaCombo;
    QComboBox* generaleCombo;
    QComboBox* acciaCombo;
    QLabel* cavalloLabel;
    QProgressBar* formaBar;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void FillCombo( QStringList fantini, QStringList contrade, Barbero * contrada, int * status );
    virtual void enableCombo1( int state );
    virtual void enableCombo2( int state );
    virtual void enableCombo3( int state );

protected:
    QVBoxLayout* StrategiaProveLayout;
    QVBoxLayout* layout23;
    QHBoxLayout* layout22;
    QSpacerItem* spacer20;
    QVBoxLayout* layout70;
    QHBoxLayout* scelta1BoxLayout;
    QHBoxLayout* layout65;
    QVBoxLayout* layout63;
    QGridLayout* layout62;
    QSpacerItem* spacer18;
    QHBoxLayout* scelta2GroupLayout;
    QHBoxLayout* layout67;
    QVBoxLayout* layout40;
    QVBoxLayout* layout42;
    QHBoxLayout* layout37;
    QSpacerItem* spacer12_4;
    QHBoxLayout* scelta3GroupLayout;
    QHBoxLayout* layout69;
    QVBoxLayout* layout41;
    QVBoxLayout* layout43;
    QHBoxLayout* layout39;
    QSpacerItem* spacer12_3;
    QVBoxLayout* layout20;
    QSpacerItem* spacer19;
    QSpacerItem* spacer19_2;
    QHBoxLayout* provaBoxLayout;
    QHBoxLayout* layout5;
    QVBoxLayout* layout3;
    QVBoxLayout* layout4;
    QHBoxLayout* layout1_2;
    QSpacerItem* spacer1_4;
    QSpacerItem* spacer1_2_2;
    QSpacerItem* spacer1_3_2;

protected slots:
    virtual void languageChange();

};

#endif // STRATEGIAPROVE_H
