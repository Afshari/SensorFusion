#ifndef QTEST_PF_ROBOT_H
#define QTEST_PF_ROBOT_H

#include <QObject>
#include <QtTest/QtTest>
#include <iostream>
#include "inc/pf_robot.h"

using Eigen::Vector2d;
using Eigen::Vector3d;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

class QTestPFRobot : public QObject {
    Q_OBJECT
public:
    explicit QTestPFRobot(QObject *parent = nullptr);

private slots:
//    void testPredict();


};

#endif // QTEST_PF_ROBOT_H
