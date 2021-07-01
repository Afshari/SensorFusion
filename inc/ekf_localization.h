#ifndef EKF_LOCALIZATION_H
#define EKF_LOCALIZATION_H

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

class EKFLocalization : public QObject {
    Q_OBJECT
public:
    explicit EKFLocalization(QObject *parent = nullptr);
    EKFLocalization(float dt, float wheelbase, float std_vel, float std_steer, QObject *parent = nullptr);
    virtual ~EKFLocalization() { };


    void predict(const unique_ptr<VectorXd> &u);
    void update(const unique_ptr<VectorXd> &z, const unique_ptr<VectorXd> &landmark);
    void setParams(float std_vel, float std_steer, float std_range,
                   float std_bearing, float start_angle, float prior_cov_pos, float prior_cov_angle);
    void setLandmarks(shared_ptr<vector<Vector2d>> landmarks);
    void setR(const float std_range, const float std_bearing);

    shared_ptr<VectorXd> get_x();
    shared_ptr<MatrixXd> get_P();
    shared_ptr<vector<Vector2d>> getLandmarks();

    void print_xP();

private:

    unique_ptr<VectorXd> x;
    unique_ptr<MatrixXd> P;
    unique_ptr<MatrixXd> F;
    unique_ptr<MatrixXd> R;
    unique_ptr<MatrixXd> Q;
    unique_ptr<VectorXd> y;

    unique_ptr<VectorXd> K;
    unique_ptr<MatrixXd> S;
    unique_ptr<MatrixXd> SI;
    unique_ptr<MatrixXd> _I;

    shared_ptr<vector<Vector2d>> landmarks;

    float std_vel;
    float std_steer;

    float a;
    float v;
    float w;
    float t;

    int dim_x;
    int dim_z;

private:
    unique_ptr<VectorXd> residual(const unique_ptr<VectorXd> &a, const unique_ptr<VectorXd> &b);
    unique_ptr<MatrixXd> HJacobian(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &landmark);
    unique_ptr<VectorXd> Hx(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &landmark);
    unique_ptr<VectorXd> move(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &u);


#if RUN_TYPE == RUN_TEST

    friend class QTestEKFLocalization;
    friend class QTestRunLocalization;
    friend class QTestInputParser;
    friend class RunLocalization;

    unique_ptr<MatrixXd> calcF(float v, float a, float theta);
    unique_ptr<MatrixXd> calcV(float v, float a, float theta);
    unique_ptr<MatrixXd> calcM(float v);
    unique_ptr<MatrixXd> calcP(const unique_ptr<MatrixXd> &prior_P, const unique_ptr<MatrixXd> &F,
                               const unique_ptr<MatrixXd> &V, const unique_ptr<MatrixXd> &M);
#endif

signals:

};

#endif // EKF_LOCALIZATION_H
