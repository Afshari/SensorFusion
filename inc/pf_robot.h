#ifndef PF_ROBOT_H
#define PF_ROBOT_H

#include <QObject>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <math.h>
#include "stats.hpp"

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

#include "inc/pf_object.h"

class PFRobot : public PFObject {
    Q_OBJECT
public:
    explicit PFRobot(QObject *parent = nullptr);
    explicit PFRobot(float x, float y, float theta, QObject *parent = nullptr);
    explicit PFRobot(shared_ptr<Vector3d> state, QObject *parent = nullptr);
    void setParams(const shared_ptr<Vector3d> &state);

#if RUN_TYPE == RUN_DEBUG

    friend class DebugServer;

#endif

};

#endif // PF_ROBOT_H
