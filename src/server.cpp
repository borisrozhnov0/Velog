#include "server.h"
#include "ui_server.h"

Server::Server(quint16 _port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
    , port{_port}
{
    ui->setupUi(this);
    str_ip = getIpAddress();

    /* init UdpSocket*/
    udp_socket = new QUdpSocket(this);
    udp_socket->bind(QHostAddress(str_ip), port);

    /* connections */
    connect(udp_socket,       &QUdpSocket::readyRead, this, &Server::readDatagram);
    connect(ui->get_button,   &QPushButton::clicked,  this, &Server::sendRequest);
    connect(ui->strat_button, &QPushButton::clicked,  this, &Server::initQML);
}

/** *
 *  @brief get corret IpAddress
 *  @return correct IP address or localhost
 */
QString Server::getIpAddress()
{
   QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            return address.toString();
    }
    return localhost.toString();
}

/** *
 *  @brief get QML Data from client
 *  Send empty Udp request on IP:Port from UI
 */
void Server::sendRequest()
{
    QByteArray data;
    udp_socket->writeDatagram(data,
                              QHostAddress(ui->line_ip_address->text()),
                              static_cast<quint16>(ui->line_port->text().toUInt()));
}

/** *
 *  @brief Listen Udp socket and response to PlainText
 *  Listen Udp socket and response to PlainText, if ip or port don't match
 *  to a ui data, then ignore it otherwise add to PlainText
 */
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

/** *
 *  @brief Start QML code from PlainText
 *  Start QML code from PlainText, if QQuickWidget already using delete it
 *  and create new QQickWidget
 */
void Server::initQML()
{
    // if QQuickWidget already using delete it
    if(container){
        if(container->rootObject()) container->rootObject()->deleteLater();
        container->deleteLater();
    }
    // create new QQuickWidget
    container = new QQuickWidget(ui->widget);
    container->setResizeMode(QQuickWidget::SizeViewToRootObject);

    // create QQmlComponent form PlainText source
    QQmlComponent component(container->engine());
    component.setData(QByteArray(ui->text_data->toPlainText().toUtf8()), QUrl());

    if(component.isError()) {
        qWarning() << "QML Error:" << component.errors();
        return;
    }
    // start QML code
    container->setContent(component.url(), &component, static_cast<QQuickItem*>(component.create()));
    container->show();
}

Server::~Server()
{
    delete ui;
}

