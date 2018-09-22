#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "ui_chatclient.h"
#include "tdpalioclient.h"

class ChatDialog : public QDialog {
    Q_OBJECT

public:
  ChatDialog(TDPalioClient* tdpalio, QWidget* parent = 0);
    ~ChatDialog();

public slots:

private:
    //int selezione[21];

    Ui::ChatClient ui;
    TDPalioClient* tdpalio;
};

#endif 
