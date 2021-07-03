
#include <QCoreApplication>
#include <iostream>

#include "inc/tcp_server.h"


int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

    TCPServer tcpServer;
    tcpServer.start();

    return a.exec();
}
