#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QLabel>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QString>
#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(quint16 _port = 12345, QWidget *parent = nullptr);
    ~Server();

private slots:
    void readDatagram();
    void sendRequest();

private:
    QString getIpAddress();
    void initQML();

    Ui::Server *ui;
    quint16 port;
    QLabel *address_lb, *port_lb;
    QUdpSocket *udp_socket;
    QQuickWidget* container = nullptr;
    QString str_ip;
};


#endif // SERVER_H
