#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "ui_webclient.h"
#include <QAbstractSocket>
#include <QTcpSocket>

class Webclient : public QWidget, private Ui::Webclient
{
    Q_OBJECT

public:
    explicit Webclient(QWidget *parent = nullptr);

private slots:
    void on_goButton_clicked();
    void on_address_returnPressed();

private:
    void connected();
    void readyRead();

    QTcpSocket *m_socket;
    QByteArray m_address;
};

#endif // WEBCLIENT_H
