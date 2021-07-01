#ifndef QTESTRUNLOCALIZATION_H
#define QTESTRUNLOCALIZATION_H

#include <QObject>
#include <QtTest/QtTest>
#include <vector>

#include "inc/run_localization.h"

using std::unique_ptr;
using std::vector;
using std::string;


class QTestRunLocalization : public QObject {
    Q_OBJECT
public:
    explicit QTestRunLocalization(QObject *parent = nullptr);


private slots:
    void testGetCode();
    void testGetIndices();
    void testGetControlInput();
    void testGetParams();
    void testGetLandmarks();
    void testGetObservations();


signals:

};

#endif // QTESTRUNLOCALIZATION_H
