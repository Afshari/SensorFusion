#ifndef _PF_PARTICLE_H
#define _PF_PARTICLE_H

#include <QObject>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <math.h>
#include <random>

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

#include "stats.hpp"
#include "inc/pf_object.h"

class PFParticle : public PFObject {
    Q_OBJECT
public:
    explicit PFParticle(QObject *parent = nullptr);
    explicit PFParticle(float x, float y, float theta, QObject *parent = nullptr);
    PFParticle(const PFParticle &p);
    PFParticle& operator=(const PFParticle& other);

    virtual void setParams(float x, float y, float theta);
    virtual void updateWeight(const shared_ptr<vector<Vector2d>>& measurements);
    virtual void moveParticle(float velocity, float theta_dot);
    virtual double pdf(float x, float mu, float sigma);

    virtual float getWeight();
    virtual float getVelocitySigma();
    virtual float getAngularVelocitySigma();

private:
    float weight;
    float distance_sigma;
    float velocity_sigma;
    float angle_sigma;
    float angular_velocity_sigma;
    float distance_domain;
    float angle_domain;

#if RUN_TYPE == RUN_TEST
    friend class QTestPFParticle;
#endif

#if RUN_TYPE == RUN_DEBUG
    friend class DebugServer;
#endif

};

#endif // _PF_PARTICLE_H
