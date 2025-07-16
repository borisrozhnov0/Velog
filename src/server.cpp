#include "server.h"
#include "ui_server.h"

Server::Server(quint16 _port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    /* UI accesse */
    addres_lb = ui->label_addres,
    port_lb = ui->label_port;

    /* init */
    initSocket(_port);


    /* connections */
    connect(upd_socket, &QUdpSocket::readyRead, this, &Server::readDatagram);

}

void Server::initSocket(quint16 port)
{
    upd_socket = new QUdpSocket(this);
    try
    {
        QHostAddress local_host = QHostAddress::LocalHost;
        upd_socket->bind(local_host, port);
        addres_lb->setText(local_host.toString());
        port_lb->setText(QString::number(port));
    }
    catch(...)
    {
        qDebug() << "Error";
    }
}

void Server::readDatagram()
{
    while(upd_socket->hasPendingDatagrams()){
        QNetworkDatagram datagram = upd_socket->receiveDatagram();
        qDebug() << datagram.data();
    }
}

Server::~Server()
{
    delete ui;
}

