#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QNetworkProxy>
#include <QTcpServer>
#include <QThread>
#include <iostream>
#include <Eigen/Dense>

#include "inc/ekf_localization.h"
#include "inc/input_parser.h"
#include "inc/run_localization.h"

using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

class TCPServer : public QObject {
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);

public slots:
    void start();
    void quit();
    void newConnection();
    void disconnected();
    void readyRead();


private:
    QTcpServer server;

    unique_ptr<RunLocalization> run_localization;
    shared_ptr<EKFLocalization> ekf;
    shared_ptr<InputParser> parser;


};

#endif // TCPSERVER_H
