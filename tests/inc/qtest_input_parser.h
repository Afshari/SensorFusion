#ifndef QTEST_INPUT_PARSER_H
#define QTEST_INPUT_PARSER_H

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
    void testGetCode();
    void testGetIndices();
    void testGetLocalizationControlInput();
    void testGetLocalizationParams();
    void testGetTrackingParams();
    void testGetLandmarks();
    void testGetObservations();


};

#endif // QTEST_INPUT_PARSER_H
