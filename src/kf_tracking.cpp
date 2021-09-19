#include "inc/kf_tracking.h"

KFTracking::KFTracking(QObject *parent) : QObject(parent) {

}

void KFTracking::init(  float init_x, float init_y,
                        float std_x, float std_y,
                        float dt, float process_noise ) {

    this->dt = dt;
    this->x = make_shared<Vector4d>( Vector4d( init_x, init_y, 0, 0 )  );

    MatrixXd t_A(4, 4);
    t_A <<   1, 0, this->dt, 0,
             0, 1, 0, 		 this->dt,
             0, 0, 1, 		 0,
             0, 0, 0,		 1;
    this->A = make_unique<MatrixXd>( t_A );

    MatrixXd t_H(2, 4);
    t_H <<  1, 0, 0, 0,
            0, 1, 0, 0;
    this->H = make_unique<MatrixXd>( t_H );

    MatrixXd t_Q(4, 4);
    t_Q <<  pow(this->dt, 4)/4,         0,                          pow(this->dt, 3)/2,         0,
            0,							pow(this->dt, 4)/4,         0,                          pow(this->dt, 3)/2,
            pow(this->dt, 3)/2,         0,							pow(this->dt, 2),           0,
            0,							pow(this->dt, 3)/2,         0,                          pow(this->dt, 2);
    this->Q = make_unique<MatrixXd>( t_Q * pow(process_noise, 2) );

    MatrixXd t_R(2, 2);
    t_R << 	pow(std_x, 2),          0,
            0,						std::pow(std_y, 2);
    this->R = make_unique<MatrixXd>( t_R );


    this->P  = make_shared<MatrixXd>( MatrixXd::Identity(4, 4) );
    this->_I = make_unique<MatrixXd>( MatrixXd::Identity(4, 4) );
}

void KFTracking::predict() {

    // x = A @ x
    this->x = make_shared<Vector4d>( (*this->A) * (*this->x) );
    // P = A @ P @ A' + Q
    this->P = make_shared<MatrixXd>( (*this->A) * (*this->P) * this->A->transpose() + (*this->Q) );
}



void KFTracking::update( const unique_ptr<VectorXd>& z ) {

    // S = H @ P @ H' + R
    MatrixXd S = (*this->H) * (*this->P) * this->H->transpose() + (*this->R);

    // K = P @ H' @ inv(S)
    MatrixXd K = (*this->P) * this->H->transpose() * S.inverse();

    // x = x + K @ (z - H @ x)
    this->x = make_shared<Vector4d>( (*this->x) + K * ( (*z) - (*this->H) * (*this->x) ) );

    // P = (I - (K @ H)) @ P
    this->P = make_shared<MatrixXd>( ( (*this->_I) - ( K * (*this->H) ) ) * (*this->P) );
}















