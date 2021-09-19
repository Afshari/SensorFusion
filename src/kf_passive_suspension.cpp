#include "inc/kf_passive_suspension.h"

KFPassiveSuspension::KFPassiveSuspension(QObject *parent) : QObject(parent) {

    this->x = make_shared<Vector4d>( Vector4d( 0, 0, 0, 0 )  );

    MatrixXd t_P(4, 4);
    t_P << 0.1,     0,      0,      0,
             0,     0,      0,      0,
             0,     0,      0,      0,
             0,     0,      0,      0;
    this->P  = make_shared<MatrixXd>( t_P );

    MatrixXd t_A(4, 4);
    t_A <<  0,       0,       1,        -1,
            0,       0,       0,         1,
           -ks/ms,   0,      -cs/ms,     cs/ms,
            ks/mu,  -kt/mu,   cs/mu,    -(cs+ct)/mu;
    this->A = make_shared<MatrixXd>( t_A );

    this->F = ltiDisc_F( this->A, this->dt );

    shared_ptr<VectorXd> L = make_shared<VectorXd>( Vector4d( 0, -1.0000, 0, 0.1285 )  );
    MatrixXd t_Qc(1, 1);
    t_Qc << this->Qc_f;
    this->Qc = make_shared<MatrixXd>( t_Qc );

    this->Q = ltiDisc_Q( this->A, L, this->Qc, this->dt );

    MatrixXd t_H(1, 4);
    t_H <<  1, 0, 0, 0;
    this->H = make_unique<MatrixXd>( t_H );


    MatrixXd t_R(1, 1);
    t_R << 	pow(1e-3, 2);
    this->R = make_unique<MatrixXd>( t_R );

    this->P  = make_shared<MatrixXd>( MatrixXd::Identity(4, 4) );
    this->_I = make_unique<MatrixXd>( MatrixXd::Identity(4, 4) );
}


shared_ptr<MatrixXd> KFPassiveSuspension::ltiDisc_F(const shared_ptr<MatrixXd> &A, float dt) {

    MatrixXd F = ( (*A) * dt ).exp();

    return make_shared<MatrixXd>( F );
}


shared_ptr<MatrixXd> KFPassiveSuspension::ltiDisc_Q(const shared_ptr<MatrixXd> &A,
                                                    const shared_ptr<VectorXd> &L,
                                                    const shared_ptr<MatrixXd> &Qc,
                                                    float dt) {
    int n = A->rows();

    MatrixXd LQcLT = (*L) * (*Qc) * L->transpose();

    MatrixXd phi_1(A->rows(), A->cols() + LQcLT.cols());
    phi_1 << (*A), LQcLT;
    MatrixXd phi_2(n, n + A->rows());
    phi_2 << MatrixXd::Zero(n, n), -A->transpose();

    MatrixXd phi(phi_1.rows() + phi_2.rows(), phi_1.cols());
    phi << phi_1, phi_2;

    MatrixXd AB_1(n+n, n);
    AB_1 << MatrixXd::Zero(n, n), MatrixXd::Identity(n, n);
    MatrixXd AB_2 = ( phi * dt ).exp();

    MatrixXd AB = AB_2 * AB_1;
    MatrixXd Q = AB.block(0, 0, n, n) * AB.block(n, 0, n, n).inverse();


    return make_shared<MatrixXd>( Q );
}


void KFPassiveSuspension::predict() {

    // x = F @ x
    this->x = make_shared<Vector4d>( (*this->F) * (*this->x) );
    // P = F @ P @ F.T + Q
    this->P = make_shared<MatrixXd>( (*this->F) * (*this->P) * this->F->transpose() + (*this->Q) );
}


void KFPassiveSuspension::update( const unique_ptr<VectorXd> &z ) {

    // S = H @ P @ H.T + R
    MatrixXd S = (*this->H) * (*this->P) * this->H->transpose() + (*this->R);
    // MatrixXd HP = (*this->H) * (*this->P);

    // K = P @ H.T @ inv(S)
    MatrixXd K = (*this->P) * this->H->transpose() * S.inverse();
    // MatrixXd PHT = (*this->P) * this->H->transpose();

    // x = x + K @ (z - H @ x)
    this->x = make_shared<Vector4d>( (*this->x) + K * ( (*z) - ((*this->H) * (*this->x)) ) );

    // P = (I - (K @ H)) @ P
    this->P = make_shared<MatrixXd>( ( (*this->_I) - ( K * (*this->H) ) ) * (*this->P) );

}















