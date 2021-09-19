#ifndef _QTEST_PF_OBJECT_H
#define _QTEST_PF_OBJECT_H

#include <QObject>
#include <QtTest/QtTest>
#include "inc/pf_object.h"

class QTestPFObject : public QObject {
    Q_OBJECT
public:
    explicit QTestPFObject(QObject *parent = nullptr);

private slots:
    void testMove();


};

#endif // _QTEST_PF_OBJECT_H
