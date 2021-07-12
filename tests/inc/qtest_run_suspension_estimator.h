#ifndef QTEST_RUN_SUSPENSION_ESTIMATOR_H
#define QTEST_RUN_SUSPENSION_ESTIMATOR_H

#include <QObject>
#include <QtTest/QtTest>
#include <vector>

#include "inc/run_suspension_estimator.h"

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;


class QTestRunSuspensionEstimator : public QObject {
    Q_OBJECT
public:
    explicit QTestRunSuspensionEstimator(QObject *parent = nullptr);

private slots:
    void testRunStep_1();
//    void testRunStep_2();


};

#endif // QTEST_RUN_SUSPENSION_ESTIMATOR_H
