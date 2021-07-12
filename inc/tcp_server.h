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
#include "inc/kf_tracking.h"
#include "inc/run_tracking.h"
#include "inc/kf_passive_suspension.h"
#include "inc/run_suspension_estimator.h"

using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

class TCPServer : public QObject {
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);

    static const int APPLICATION_EKF_LOCALIZATION = 1;
    static const int APPLICATION_KF_TRACKING = 2;
    static const int APPLICATION_KF_PASSIVE_SUSPENSION = 3;


public slots:
    void start(int typeOfApplication);
    void quit();
    void newConnection();
    void disconnected();
    void readyRead();


private:
    QTcpServer server;

    int typeOfApplication = 0;

    unique_ptr<RunLocalization> run_localization;
    shared_ptr<EKFLocalization> ekf;

    unique_ptr<RunTracking> run_tracking;
    shared_ptr<KFTracking> kf;

    unique_ptr<RunSuspensionEstimator> run_suspension_estimator;
    shared_ptr<KFPassiveSuspension> suspension_estimator;


    shared_ptr<InputParser> parser;

};

#endif // TCPSERVER_H
