#ifndef _QTEST_INPUT_PARSER_H
#define _QTEST_INPUT_PARSER_H

#include <QObject>
#include <QtTest/QtTest>
#include <vector>

#include "inc/input_parser.h"

using std::unique_ptr;
using std::vector;
using std::string;


class QTestInputParser : public QObject {
    Q_OBJECT
public:
    explicit QTestInputParser(QObject *parent = nullptr);

private slots:
    void testCheckInput();
    void testGetCode();
    void testGetIndices();
    void testGetLocalizationControlInput();
    void testGetLocalizationParams();
    void testGetTrackingParams();
    void testGetLandmarks();
    void testGetObservations();
    void testGetSuspensionObservations();


};

#endif // _QTEST_INPUT_PARSER_H
