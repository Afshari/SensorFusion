#ifndef EXTENDEDKALMANFILTER_H
#define EXTENDEDKALMANFILTER_H

#include <QObject>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <math.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Vector2d;
using std::unique_ptr;
using std::make_unique;


class EKFLocalization : public QObject {
    Q_OBJECT
public:
    explicit EKFLocalization(float dt, float wheelbase, float std_vel, float std_steer, QObject *parent = nullptr);
    virtual ~EKFLocalization() { };


private:

    std::unique_ptr<VectorXd> x;
    std::unique_ptr<MatrixXd> P;
    std::unique_ptr<MatrixXd> F;
    std::unique_ptr<MatrixXd> R;
    std::unique_ptr<MatrixXd> Q;
    std::unique_ptr<VectorXd> y;

    std::unique_ptr<VectorXd> K;
    std::unique_ptr<MatrixXd> S;
    std::unique_ptr<MatrixXd> SI;
    std::unique_ptr<MatrixXd> _I;

    float dt;
    float std_vel;
    float std_steer;

    float a;
    float v;
    float w;
    float t;
    float theta;

    int dim_x;
    int dim_z;
    int dim_u;


    void predict(const unique_ptr<VectorXd> &u);
    void update(const unique_ptr<VectorXd> &z, const unique_ptr<VectorXd> &landmark);
    void setR(const float std_range, const float std_bearing);

private:
    unique_ptr<VectorXd> residual(const unique_ptr<VectorXd> &a, const unique_ptr<VectorXd> &b);
    unique_ptr<MatrixXd> HJacobian(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &landmark);
    unique_ptr<VectorXd> Hx(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &landmark);
    unique_ptr<VectorXd> move(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &u);


#if RUN_TYPE == RUN_TEST

    friend class QTestEKFLocalization;

    unique_ptr<MatrixXd> calcF(float v, float a, float theta);
    unique_ptr<MatrixXd> calcV(float v, float a, float theta);
    unique_ptr<MatrixXd> calcM(float v);
    unique_ptr<MatrixXd> calcP(const unique_ptr<MatrixXd> &prior_P, const unique_ptr<MatrixXd> &F,
                               const unique_ptr<MatrixXd> &V, const unique_ptr<MatrixXd> &M);
#endif

signals:

};

#endif // EXTENDEDKALMANFILTER_H
