#include "inc/debug_server.h"

DebugServer::DebugServer(QObject *parent) : QObject(parent) {

    connect(&server, &QTcpServer::newConnection, this, &DebugServer::newConnection);

}

void DebugServer::start(int typeOfApplication) {

    this->typeOfApplication = typeOfApplication;

    server.listen(QHostAddress::Any, 6060);
    std::cout << "Waiting for a New Connection..." << std::endl;
}

void DebugServer::quit() {

    server.close();
}

void DebugServer::newConnection() {

    QTcpSocket *socket = server.nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &DebugServer::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &DebugServer::readyRead);

    qInfo() << "connected: " << socket;
}

void DebugServer::disconnected() {

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    qInfo() << "Disconnected" << socket;
    qInfo() << "Parent" << socket->parent();

    socket->deleteLater();
}


void DebugServer::readyRead() {

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QString received = QString::fromUtf8( socket->readAll() );

    std::string data = received.toUtf8().constData();

    std::cout << "data: " << data << std::endl;
    shared_ptr<vector<int>> indices = input_parser.getIndices(data, ":");
    shared_ptr<Vector3d> state = input_parser.getPFLocalizationParams(data, indices->at(1), data.length() - indices->at(1));

    PFRobot robot(state);

    int code = input_parser.getCode(data);
    std::cout << "code: " << code << std::endl;

    string response = "OK";
    socket->write( response.c_str(), response.length() );


}














