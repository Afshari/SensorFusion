#ifndef QTEST_RUN_LOCALIZATION_H
#define QTEST_RUN_LOCALIZATION_H

#include <QObject>
#include <QtTest/QtTest>
#include <vector>

#include "inc/run_localization.h"

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;


class QTestRunLocalization : public QObject {
    Q_OBJECT
public:
    explicit QTestRunLocalization(QObject *parent = nullptr);


private slots:
    void testRunStep_1();
    void testRunStep_2();


signals:

};

#endif // QTEST_RUN_LOCALIZATION_H
