/****************************************************************************
** Form interface generated from reading ui file 'browsecd.ui'
**
** Created: Sat Dec 16 17:05:03 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef BROWSECD_H
#define BROWSECD_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QComboBox;
class groupBoxControl;
class QRadioButton;
class QTextEdit;
class QPushButton;

class browseCD : public QDialog
{
    Q_OBJECT

public:
    browseCD( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~browseCD();

    QLabel* authorLabel;
    QLineEdit* authorEdit;
    QLabel* titleLabel;
    QLineEdit* titleEdit;
    QLabel* supplierLabel;
    QLabel* companyLabel;
    QLineEdit* supplierEdit;
    QLineEdit* companyEdit;
    QLabel* formatLabel;
    QLabel* Code;
    QLineEdit* formatEdit;
    QLineEdit* codeEdit;
    QLabel* retailPriceLabel;
    QLabel* sellingPriceLabel;
    QLineEdit* sellingPriceEdit;
    QLabel* specialPriceLabel;
    QLineEdit* specialPriceEdit;
    QLineEdit* retailPriceEdit;
    groupBoxControl* statusBox;
    QRadioButton* normalCheck;
    QRadioButton* newCheck;
    QRadioButton* offertCheck;
    QRadioButton* deletedCheck;
    QLabel* orderedLabel;
    QLabel* stockLabel;
    QLineEdit* stockEdit;
    QLineEdit* soldEdit;
    QLineEdit* orderedEdit;
    QLabel* soldLabel;
    QLabel* noteLabel;
    QTextEdit* noteTextEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void reject();
    virtual void accept();

protected:
    QVBoxLayout* browseCDLayout;
    QVBoxLayout* layout24;
    QSpacerItem* spacer32;
    QSpacerItem* spacer33;
    QSpacerItem* spacer34;
    QSpacerItem* spacer34_2;
    QGridLayout* layout35;
    QHBoxLayout* layout54;
    QSpacerItem* spacer22;
    QSpacerItem* spacer26;
    QHBoxLayout* layout53;
    QVBoxLayout* layout51;
    QVBoxLayout* layout52;
    QHBoxLayout* layout50;
    QVBoxLayout* layout48;
    QVBoxLayout* layout49;
    QHBoxLayout* layout15;
    QSpacerItem* spacer30;
    QSpacerItem* spacer31;
    QGridLayout* layout37;
    QVBoxLayout* statusBoxLayout;
    QVBoxLayout* layout14;
    QGridLayout* layout44;
    QHBoxLayout* layout23;
    QVBoxLayout* layout22;
    QSpacerItem* spacer34_3;
    QHBoxLayout* layout43;
    QSpacerItem* spacer27;
    QSpacerItem* spacer28;
    QSpacerItem* spacer29;

protected slots:
    virtual void languageChange();

};

#endif // BROWSECD_H
