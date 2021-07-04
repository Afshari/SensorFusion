#ifndef QTEST_KF_LOCALIZATION_H
#define QTEST_KF_LOCALIZATION_H

#include <QObject>
#include <QtTest/QtTest>
#include <iostream>
#include "inc/kf_tracking.h"

using Eigen::Vector2d;
using Eigen::Vector3d;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;


class QTestKFTracking : public QObject {
    Q_OBJECT
public:
    explicit QTestKFTracking(QObject *parent = nullptr);

private slots:

    void testConstructor();
    void testPredict();
    void testUpdate();

signals:

};

#endif // QTEST_KF_LOCALIZATION_H
