#include "server.h"
#include "ui_server.h"

Server::Server(quint16 _port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    /* UI accesse */
    address_lb = ui->label_addres,
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
        QHostAddress local_host = QHostAddress(getIpAddress());
        upd_socket->bind(local_host, port);
        address_lb->setText(local_host.toString());
        port_lb->setText(QString::number(port));
    }
    catch(...)
    {
        qDebug() << "Error";
    }
}

QString Server::getIpAddress()
{
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            return address.toString();
    }
    return "Unknown";
}


void Server::readDatagram()
{
    while(upd_socket->hasPendingDatagrams()){
        QNetworkDatagram datagram = upd_socket->receiveDatagram();

        if(!container){
            container = new QQuickWidget(this);
            container->setResizeMode(QQuickWidget::SizeViewToRootObject);
        }
        else {
            if(container->rootObject()) container->rootObject()->deleteLater();
        }
        QQmlComponent component(container->engine());
        component.setData(datagram.data(), QUrl());

        if(component.isError()) {
            qWarning() << "QML Error:" << component.errors();
            continue;
        }
        container->setContent(component.url(), &component, static_cast<QQuickItem*>(component.create()));
        container->show();
    }
}

Server::~Server()
{
    delete ui;
}

