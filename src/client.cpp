#include "client.h"
#include "ui_client.h"

Client::Client(quint16 _port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
    , port{_port}
{
    ui->setupUi(this);

    str_ip = getIpAddress();
    str_port = QString::number(port);

    /* UI access */
    address_le = ui->label_client_ip;
    port_le = ui->label_port;
    data_pte = ui->Text_send;

    /* Update UI */
    ui->label_client_ip->setText("Ip: " + str_ip);
    ui->label_port->setText("Port: " + str_port);

    /* init UdpSocket */
    udp_socket = new QUdpSocket(this);
    QHostAddress host(str_ip);
    udp_socket->bind(host, port);

    /* Connections */
    connect(ui->save_button, &QPushButton::clicked,  this, &Client::saveFile);
    connect(ui->load_button, &QPushButton::clicked,  this, &Client::loadFile);
    connect(udp_socket,      &QUdpSocket::readyRead, this, &Client::sendDatagram);
}

Client::~Client()
{
    delete ui;
}

/** *
 *  @brief get corret IpAddress
 *  @return correct IP address or localhost
*/
QString Client::getIpAddress()
{
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            return address.toString();
    }
    return localhost.toString();
}

/** *
 * @brief Send datagram to client
 *
 * Listen udp socket and send data from PlanTextEdit to sender
 */
void Client::sendDatagram()
{
    while(udp_socket->hasPendingDatagrams()){
        /* Get sender data */
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        QHostAddress sender_ip = datagram.senderAddress();
        quint16 sender_port = datagram.senderPort();

        /* Send response */
        udp_socket->writeDatagram(data_pte->toPlainText().toUtf8(), sender_ip, sender_port);
    }
}

/** *
 *  @brief Save file
 */
void Client::saveFile()
{
    // Get filename
    QString file_name = QFileDialog::getSaveFileName(this, "Save file", "", "QML files (*.qml);;All files (*.*)");
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly)){
        qWarning() << "Error save: " << file.error();
        return;
    }

    // Save data if file
    QByteArray data(data_pte->toPlainText().toUtf8());
    file.write(data);
    file.close();
}

/** *
 *  @brief Load file
 *  Load file and add data to the PlainText
 */
void Client::loadFile()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Load file", "", "QML files (*.qml);;All files (*.*)");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly)){
        qWarning() << "Error save: " << file.error();
        return;
    }

    QByteArray data(file.readAll());
    data_pte->setPlainText(QString::fromUtf8(data));
}
