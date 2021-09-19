#ifndef _QTEST_PF_PARTICLE_H
#define _QTEST_PF_PARTICLE_H

#include <QObject>
#include <QtTest/QtTest>
#include <vector>

#include "inc/pf_particle.h"

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;

class QTestPFParticle : public QObject {
    Q_OBJECT
public:
    explicit QTestPFParticle(QObject *parent = nullptr);

private slots:
    void testConstructor();
    void testUpdateWeight();



};

#endif // _QTEST_PF_PARTICLE_H
