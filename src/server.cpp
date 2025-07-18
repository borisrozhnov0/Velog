#include "server.h"
#include "ui_server.h"

Server::Server(quint16 _port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
    , port{_port}
{
    ui->setupUi(this);
    str_ip = getIpAddress();


    /* init upd_socket*/
    udp_socket = new QUdpSocket(this);
    udp_socket->bind(QHostAddress(str_ip), port);

    /* connections */
    connect(udp_socket,       &QUdpSocket::readyRead, this, &Server::readDatagram);
    connect(ui->get_button,   &QPushButton::clicked,  this, &Server::sendRequest);
    connect(ui->strat_button, &QPushButton::clicked,  this, &Server::initQML);
}

QString Server::getIpAddress()
{
   QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            return address.toString();
    }
    return localhost.toString();
}

void Server::sendRequest()
{
    QByteArray data;
    udp_socket->writeDatagram(data,
                              QHostAddress(ui->line_ip_address->text()),
                              static_cast<quint16>(ui->line_port->text().toUInt()));
}


void Server::readDatagram()
{
    while(udp_socket->hasPendingDatagrams()){
        QNetworkDatagram datagram = udp_socket->receiveDatagram();

        if(datagram.senderAddress() != QHostAddress(ui->line_ip_address->text()) || datagram.senderPort() != static_cast<quint16>(ui->line_port->text().toUInt())){
            continue;
        }
        ui->text_data->setPlainText(QString::fromUtf8(datagram.data()));
    }
}

void Server::initQML()
{
    if(container){
        if(container->rootObject()) container->rootObject()->deleteLater();
        container->deleteLater();
    }
    container = new QQuickWidget(ui->widget);
    container->setResizeMode(QQuickWidget::SizeViewToRootObject);

    QQmlComponent component(container->engine());
    component.setData(QByteArray(ui->text_data->toPlainText().toUtf8()), QUrl());

    if(component.isError()) {
        qWarning() << "QML Error:" << component.errors();
        return;
    }
    container->setContent(component.url(), &component, static_cast<QQuickItem*>(component.create()));
    container->show();
}

Server::~Server()
{
    delete ui;
}

