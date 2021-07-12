#ifndef KF_PASSIVE_SUSPENSION_H
#define KF_PASSIVE_SUSPENSION_H

#include <QObject>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
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


class KFPassiveSuspension : public QObject {
    Q_OBJECT
public:
    explicit KFPassiveSuspension(QObject *parent = nullptr);
    virtual void predict();
    virtual void update( const unique_ptr<VectorXd>& z );

    virtual shared_ptr<MatrixXd> ltiDisc_F(const shared_ptr<MatrixXd> &A, float dt);
    virtual shared_ptr<MatrixXd> ltiDisc_Q(const shared_ptr<MatrixXd> &A,
                                           const shared_ptr<VectorXd> &L,
                                           const shared_ptr<MatrixXd> &Qc,
                                           float dt);

    shared_ptr<Vector4d> get_x() { return this->x; }
    shared_ptr<MatrixXd> get_P() { return this->P; }

private:    

    // Model Parameters
    const float ms = 972.2;                   // Sprung mass
    const float mu = 113.6;                   // Unsprung mass
    const float ks = 42719.6;                 // Stiffness of the suspension
    const float kt = 101115;                  // Compressibility of the tire
    const float cs = 1095;                    // Damping of the suspension
    const float ct = 14.6;                    // Damping of the pneumatic tyre
    const float dt = 0.001;                   // Stepsize

    // Time production
    const int Tf = 8;
    const int n = int( Tf / dt );

    // Process noise variance
    const float n0 = 0.1;                      // Reference spatial frequency
    const float V  = 25/3.6;                   // Vehicle forward velocity (m/s)
    const float Gqn0 = 256*1e-6;               // Road roughness coefficient

    const float Qc_f = 4 * M_PI * Gqn0 * pow(n0, 2) * V;


    shared_ptr<Vector4d> x;
    shared_ptr<MatrixXd> P;
    shared_ptr<MatrixXd> A;
    shared_ptr<MatrixXd> F;
    unique_ptr<MatrixXd> H;
    shared_ptr<MatrixXd> Q;
    shared_ptr<MatrixXd> Qc;
    unique_ptr<MatrixXd> R;
    unique_ptr<MatrixXd> _I;

#if RUN_TYPE == RUN_TEST

    friend class QTestKFPassiveSuspension;

#endif

};

#endif // KF_PASSIVE_SUSPENSION_H
