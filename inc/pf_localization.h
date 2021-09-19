#ifndef _PF_LOCALIZATION_H
#define _PF_LOCALIZATION_H

#include <QObject>
#include <Eigen/Dense>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <typeinfo>
#include <math.h>
#include <random>
#include <numeric>
#include <algorithm>

#include "inc/pf_robot.h"
#include "inc/pf_particle.h"

using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::VectorXd;
using Eigen::Vector2d;
using Eigen::Vector3d;

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::string;

class PFLocalization : public QObject {
    Q_OBJECT
public:
    explicit PFLocalization(const shared_ptr<PFRobot> &robot, QObject *parent = nullptr);
    virtual void setRobotParam(const shared_ptr<Vector3d> &state);
    virtual void setRobotMeasurements(shared_ptr<vector<Vector2d>> measurements);
    virtual void robotMove(float velocity, float angular_velocity);
    virtual void setParticleMeasurements(int idx, shared_ptr<vector<Vector2d>> measurements);
    virtual void updateParticleWeight(int idx, shared_ptr<vector<Vector2d>> measurements);
    virtual void predictParticle(int idx, float velocity, float angular_velocity);
    virtual void generateParticles();
    virtual void resample();
    virtual uint numberOfParticles();
    virtual string getAllStateString();

protected:
    shared_ptr<PFRobot> robot;
    vector<PFParticle> particles;

signals:

};

#endif // _PF_LOCALIZATION_H
