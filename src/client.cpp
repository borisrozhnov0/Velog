#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    /* UI access */
    address_le = ui->Line_Address;
    port_le = ui->Line_port;
    data_pte = ui->Text_send;

    /* Connection */
    connect(ui->Button_send, &QPushButton::clicked, this, &Client::sendDatagram);

}

Client::~Client()
{
    delete ui;
}

void Client::sendDatagram()
{
    try
    {
        /* Init socket data */
        QByteArray data = data_pte->toPlainText().toUtf8();
        QHostAddress address(address_le->text());
        quint16 port = port_le->text().toInt();
        QUdpSocket *socket = new QUdpSocket;

        /* Send dtg */
        socket->writeDatagram(data, address, port);

        /* Delate socket */
        socket->deleteLater();
    }
    catch(...)
    {
        qDebug() << "Client Error\n";
    }

}
