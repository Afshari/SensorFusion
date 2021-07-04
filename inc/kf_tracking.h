#ifndef KF_TRACKING_H
#define KF_TRACKING_H

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
using Eigen::Vector4d;

using std::vector;
using std::pow;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;


class KFTracking : public QObject {
    Q_OBJECT
public:
    explicit KFTracking(QObject *parent = nullptr);

    virtual void init(  float init_x, float init_y,
                        float std_x, float std_y,
                        float dt, float process_noise );
    virtual void predict();
    virtual void update( const unique_ptr<VectorXd>& z );


private:

    shared_ptr<Vector4d> x;
    shared_ptr<MatrixXd> P;
    unique_ptr<MatrixXd> A;
    unique_ptr<MatrixXd> H;
    unique_ptr<MatrixXd> Q;
    unique_ptr<MatrixXd> R;
    unique_ptr<MatrixXd> _I;

    float dt;


#if RUN_TYPE == RUN_TEST

    friend class QTestKFTracking;
#endif

};

#endif // KF_TRACKING_H













