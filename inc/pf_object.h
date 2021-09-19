#ifndef PF_OBJECT_H
#define PF_OBJECT_H

#include <QObject>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <math.h>

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

class PFObject : public QObject {
    Q_OBJECT
public:
    explicit PFObject(float x, float y, float theta, QObject *parent = nullptr);
    PFObject(shared_ptr<Vector3d> state, QObject *parent = nullptr);

    virtual void move(float velocity, float angular_velocity);
    virtual void setMeasurements(shared_ptr<vector<Vector2d>> measurements);

    float getX();
    float getY();
    float getTheta();

protected:
    float x;
    float y;
    float theta;
    shared_ptr<vector<Vector2d>> measurements;

#if RUN_TYPE == RUN_TEST

    friend class QTestPFObject;

#endif

#if RUN_TYPE == RUN_DEBUG

    friend class DebugServer;

#endif

};

#endif // PF_OBJECT_H
