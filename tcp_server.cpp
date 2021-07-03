#include "inc/tcp_server.h"

TCPServer::TCPServer(QObject *parent) : QObject(parent) {

    connect(&server, &QTcpServer::newConnection, this, &TCPServer::newConnection);

    run_localization = make_unique<RunLocalization>();
    ekf = make_shared<EKFLocalization>( 0.1, 0.5, 0.1, 0.1 );
    parser = make_shared<InputParser>();

}


void TCPServer::start() {

    server.listen(QHostAddress::Any, 5091);
    std::cout << "Waiting for a New Connection..." << std::endl;
}

void TCPServer::quit() {

    server.close();
}

void TCPServer::newConnection() {

    QTcpSocket *socket = server.nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &TCPServer::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TCPServer::readyRead);

    qInfo() << "connected: " << socket;
}

void TCPServer::disconnected() {

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    qInfo() << "Disconnected" << socket;
    qInfo() << "Parent" << socket->parent();

    socket->deleteLater();
}


void TCPServer::readyRead() {

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QString received = QString::fromUtf8( socket->readAll() );

    std::string data = received.toUtf8().constData();
//    std::cout << data << std::endl;

    run_localization->step(data, ekf, parser);
    std::ostringstream stringStream;
    stringStream << (*ekf->get_x())(0) << "," << (*ekf->get_x())(1) << "," << (*ekf->get_x())(2) ;

    std::string response = stringStream.str();

//    std::cout << response << std::endl;

    socket->write( response.c_str(), response.length() );

}
















