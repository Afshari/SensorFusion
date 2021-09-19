#ifndef DEBUGSERVER_H
#define DEBUGSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QNetworkProxy>
#include <QTcpServer>
#include <QThread>
#include <iostream>

#include "inc/input_parser.h"
#include "inc/pf_robot.h"

class DebugServer : public QObject
{
    Q_OBJECT
public:
    explicit DebugServer(QObject *parent = nullptr);

public slots:
    void start(int typeOfApplication);
    void quit();
    void newConnection();
    void disconnected();
    void readyRead();


private:
    QTcpServer server;
    InputParser input_parser;

    int typeOfApplication = 0;

};

#endif // DEBUGSERVER_H
