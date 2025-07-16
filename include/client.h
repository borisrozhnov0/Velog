#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QUdpSocket>
#include <QByteArray>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void sendDatagram();

private:
    Ui::Client *ui;
    QPushButton *send_bt;
    QLineEdit *address_le, *port_le;
    QPlainTextEdit *data_pte;
};

#endif // CLIENT_H
