#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QUdpSocket>
#include <QByteArray>
#include <QFileDialog>
#include <QNetworkDatagram>
#include <QNetworkInterface>


namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(quint16 _port = 2222, QWidget *parent = nullptr);
    ~Client();

private slots:
    void sendDatagram();
    void saveFile();
    void loadFile();

private:
    Ui::Client *ui;
    quint16 port;
    QUdpSocket * udp_socket;
    QString getIpAddress();
    QString str_ip, str_port;
    QPushButton *send_bt;
    QLabel *address_le, *port_le;
    QPlainTextEdit *data_pte;


};

#endif // CLIENT_H
