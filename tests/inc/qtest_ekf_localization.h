#ifndef QTEST_EKF_H
#define QTEST_EKF_H

#include <QObject>
#include <QtTest/QtTest>
#include <iostream>
#include "inc/ekf_localization.h"

using Eigen::Vector2d;
using Eigen::Vector3d;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

class QTestEKFLocalization : public QObject {
    Q_OBJECT
public:
    explicit QTestEKFLocalization(QObject *parent = nullptr);
    virtual ~QTestEKFLocalization() { };


private slots:
    void testConstructor_1();
    void testConstructor_2();
    void testResidual();
    void testHJacobian();
    void testHx();
    void testMove();
    void testCalcF();
    void testCalcV();
    void testCalcM();
    void testCalcP();
    void testPredict();
    void testUpdate();


};

#endif // QTEST_EKF_H
