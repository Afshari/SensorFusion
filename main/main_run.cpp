
#include <QCoreApplication>
#include <iostream>

#include "inc/tcp_server.h"


int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

    int typeOfApplication = 0;
    std::string value;

    qDebug() << "Select Type of Application";
    qDebug() << "1. Extended Kalman Filter Localization";
    qDebug() << "2. Kalman Filter Tracking";

    std::cin >> typeOfApplication;


    if(typeOfApplication == TCPServer::APPLICATION_EKF_LOCALIZATION) {
        qDebug() << "You are running Extended Kalman Filter Localization Application";
    } else if(typeOfApplication == TCPServer::APPLICATION_KF_TRACKING) {
        qDebug() << "You are running Kalman Filter Tracking Application";
    } else {
        qDebug() << "You Chose a Wrong Option";
        exit(-1);
    }

    TCPServer tcpServer;
    tcpServer.start(typeOfApplication);

    return a.exec();
}
