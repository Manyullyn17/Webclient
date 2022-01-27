#include "webclient.h"
#include <QColor>

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &Webclient::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::readyRead);

    setupUi(this);
}

void Webclient::on_goButton_clicked()
{
    unsigned short port = 80;

    QString str = address->text();
    m_address += str;

    m_socket->connectToHost(m_address, port);
    if (!m_socket->waitForConnected(5000)) {
        output->clear();
        QColor getColor;
        output->setTextColor(getColor.fromRgb(255, 0, 0, 255));
        output->setText("Connect failed!");
    }
}

void Webclient::on_address_returnPressed()
{
    on_goButton_clicked();
}

void Webclient::connected()
{
    m_socket->write("GET / HTTP/1.1\r\nHost:" + m_address + "\r\n\r\n");
}

void Webclient::readyRead()
{
    output->clear();
    QColor getColor;
    output->setTextColor(getColor.fromRgb(0, 0, 0, 255));
    output->setText(m_socket->readAll());
    m_socket->disconnectFromHost();
}
