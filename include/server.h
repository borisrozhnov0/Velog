#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QLabel>
#include <QUdpSocket>
#include <QNetworkDatagram>


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

    Ui::Server *ui;
    QLabel *addres_lb, *port_lb;
    QUdpSocket * upd_socket;

};


#endif // SERVER_H
