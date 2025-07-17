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

private:
    void initSocket(quint16 port);
    QString getIpAddress();
    Ui::Server *ui;
    QLabel *address_lb, *port_lb;
    QUdpSocket * upd_socket;
    QQuickWidget* container = nullptr;
};


#endif // SERVER_H
