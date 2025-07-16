#include <QApplication>
#include "server.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Server server(2234);
    server.show();
    Client client;
    client.show();

    return a.exec();
}
