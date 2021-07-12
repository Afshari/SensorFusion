#ifndef QTEST_KF_AIR_SUSPENSION_H
#define QTEST_KF_AIR_SUSPENSION_H

#include <QObject>
#include <QtTest/QtTest>
#include <iostream>
#include <unsupported/Eigen/MatrixFunctions>
#include "inc/kf_passive_suspension.h"

using Eigen::Vector2d;
using Eigen::Vector3d;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

class QTestKFPassiveSuspension : public QObject {
    Q_OBJECT
public:
    explicit QTestKFPassiveSuspension(QObject *parent = nullptr);

private slots:
    void testLtiDisc_F();
    void testLtiDisc_Q();
    void testPredict();
    void testUpdate_1();
    void testUpdate_2();
    void testStep();

signals:

};

#endif // QTEST_KF_AIR_SUSPENSION_H
