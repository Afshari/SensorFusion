
#include "inc/ekf_localization.h"

EKFLocalization::EKFLocalization(QObject *parent) : QObject(parent) {

    this->dim_x = 3;
    this->dim_z = 2;
//    this->dim_u = 2;

    this->x = make_unique<VectorXd>( VectorXd::Zero(this->dim_x, 1) );                   // State
    this->P = make_unique<MatrixXd>( MatrixXd::Identity(this->dim_x, this->dim_x) );     // Uncertainty Covariance
    this->F = make_unique<MatrixXd>( MatrixXd::Identity(this->dim_x, this->dim_x) );     // State Transition Matrix
    this->R = make_unique<MatrixXd>( MatrixXd::Identity(this->dim_z, this->dim_z) );     // State Uncertainty
    this->Q = make_unique<MatrixXd>( MatrixXd::Identity(this->dim_x, this->dim_x) );     // Process Uncertainty
    this->y = make_unique<VectorXd>( VectorXd::Zero(this->dim_z, 1) );                   // Residual

//    z = np.array([None]*self.dim_z)
//    self.z = reshape_z(z, self.dim_z, self.x.ndim)

    this->K  = make_unique<VectorXd>( VectorXd::Zero(this->dim_x, 1) );                  // Kalman Gain
    this->S  = make_unique<MatrixXd>( MatrixXd::Zero(this->dim_z, this->dim_z) );        // system uncertainty
    this->SI = make_unique<MatrixXd>( MatrixXd::Zero(this->dim_z, this->dim_z) );        // inverse system uncertainty

    this->_I = make_unique<MatrixXd>( MatrixXd::Identity(this->dim_x, this->dim_x) );

//    this->dt = 0;
    this->std_vel = 0;
    this->std_steer = 0;

    this->a = 0;
    this->v = 0;
    this->w = 0.5;
    this->t = 1;
}


EKFLocalization::EKFLocalization(float dt, float wheelbase, float std_vel, float std_steer, QObject *parent) :
    EKFLocalization(parent) {

//    this->dt = dt;
    this->std_vel = std_vel;
    this->std_steer = std_steer * M_PI / 180;

//    this->a = 0;
//    this->v = 0;
    this->w = wheelbase;
    this->t = dt;
//    this->theta = 0;
}

void EKFLocalization::setParams(float std_vel, float std_steer, float std_range,
               float std_bearing, float start_angle, float prior_cov_pos, float prior_cov_angle) {

    this->std_vel = std_vel;
    this->std_steer = std_steer * M_PI / 180;
    setR(std_range, std_bearing);
    this->x = make_unique<VectorXd>( Vector3d( { 0, 0, start_angle } ) );
    MatrixXd P(3, 3);
    P << prior_cov_pos, 0,             0,
         0,             prior_cov_pos, 0,
         0,             0,             prior_cov_angle;
    this->P = make_unique<MatrixXd>( P );
}


void EKFLocalization::setLandmarks(unique_ptr<vector<Vector2d>> landmarks) {

    this->landmarks = std::move( landmarks );
}


unique_ptr<VectorXd> EKFLocalization::residual(const unique_ptr<VectorXd> &a,
                                               const unique_ptr<VectorXd> &b) {

    VectorXd res = (*a) - (*b);
    res(1) = std::fmod(res(1), 2 * M_PI);
    if(res(1) > M_PI)
        res(1) -= 2 * M_PI;

    return make_unique<VectorXd>( res );
}

unique_ptr<MatrixXd> EKFLocalization::HJacobian(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &landmark) {

    float px = landmark->data()[0];
    float py = landmark->data()[1];

    float hyp = pow(px - x->data()[0], 2) + pow(py - x->data()[1], 2);
    float dist = sqrt(hyp);

    MatrixXd H(2, 3);
    H << -(px - x->data()[0]) / dist, -(py - x->data()[1]) / dist, 0,
          (py - x->data()[1]) / hyp,  -(px - x->data()[0]) / hyp, -1 ;

    return make_unique<MatrixXd>( H );
}


unique_ptr<VectorXd> EKFLocalization::Hx(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &landmark) {

    float px = landmark->data()[0];
    float py = landmark->data()[1];
    float dist = sqrt( pow(px - x->data()[0], 2) + pow(py - x->data()[1], 2) );
    float angle = atan2( py - x->data()[1], px - x->data()[0] ) - x->data()[2];

    return make_unique<VectorXd>( Vector2d( dist, angle  ) );
}


unique_ptr<VectorXd> EKFLocalization::move(const unique_ptr<VectorXd> &x, const unique_ptr<VectorXd> &u) {

    float r = u->data()[0];
    float angle = u->data()[1];

    VectorXd res(3);

    if(std::abs( angle ) > 0.001) {

        res << x->data()[0] + ( r * cos( angle )  / 10 ) ,
               x->data()[1] + ( r * sin( angle )  / 10 ) ,
               x->data()[2] + angle;
    } else {

        res << x->data()[0] + ( r * cos( angle )  / 10 ) ,
               x->data()[1] + ( r * sin( angle )  / 10 ) ,
               x->data()[2] + 1e-5;
    }

    return make_unique<VectorXd>( res );
}

void EKFLocalization::predict(const unique_ptr<VectorXd> &u) {

    this->x = move(this->x, u);

    float theta = x->data()[2];
    float v = u->data()[0];
    float a = u->data()[1];

    MatrixXd F(3, 3);
    F << 1, 0, (-w * cos(theta) / tan(a)) + (w * cos(t * v * tan(a) / w + theta) / tan(a)) ,
         0, 1, (-w * sin(theta) / tan(a)) + (w * sin(t * v * tan(a) / w + theta) / tan(a)) ,
         0, 0, 1;

    MatrixXd V(3, 2);
    V <<    t * cos(t * v * tan(a) / w + theta), t * v * (pow(tan(a), 2) + 1) * cos(t * v * tan(a) / w + theta) / tan(a) - w * (-pow(tan(a), 2) - 1) * sin(theta) / pow(tan(a), 2) + w * (-pow(tan(a), 2) - 1) * sin(t * v * tan(a) / w + theta) / pow(tan(a), 2),
            t * sin(t * v * tan(a) / w + theta), t * v * (pow(tan(a), 2) + 1) * sin(t * v * tan(a) / w + theta) / tan(a) + w * (-pow(tan(a), 2) - 1) * cos(theta) / pow(tan(a), 2) - w * (-pow(tan(a), 2) - 1) * cos(t * v * tan(a) / w + theta) / pow(tan(a), 2),
            t * tan(a) / w, t * v * (pow(tan(a), 2) + 1) / w;

    MatrixXd M(2, 2);
    M << this->std_vel * pow(v, 2),   0,
         0,                           pow(this->std_steer, 2);

    this->P = make_unique<MatrixXd>( F * (*this->P) * F.transpose()  + V * M * V.transpose() );
}

void EKFLocalization::update(const unique_ptr<VectorXd> &z, const unique_ptr<VectorXd> &landmark) {

    unique_ptr<MatrixXd> H = HJacobian(this->x, landmark);
    MatrixXd PHT = (*this->P) * H->transpose();
    MatrixXd S = (*H) * PHT + (*this->R);
    MatrixXd SI = S.inverse();
    MatrixXd K = PHT * SI;
    unique_ptr<VectorXd> hx = Hx(this->x, landmark);
    unique_ptr<VectorXd> y = residual(z, hx);
    this->x = make_unique<VectorXd>( (*this->x) + K * (*y) );

    MatrixXd I_KH = (*_I) - K * (*H);
    this->P = make_unique<MatrixXd>( I_KH * (*this->P) * I_KH.transpose() + K * (*this->R) * K.transpose() );
}

void EKFLocalization::setR(const float std_range, const float std_bearing) {

    MatrixXd r(2, 2);
    r << pow(std_range, 2),     0,
         0,                     pow(std_bearing, 2);
    this->R = make_unique<MatrixXd>( r );
}


#if RUN_TYPE == RUN_TEST

unique_ptr<MatrixXd> EKFLocalization::calcF(float v, float a, float theta) {

    MatrixXd F(3, 3);
    F << 1, 0, (-w * cos(theta) / tan(a)) + (w * cos(t * v * tan(a) / w + theta) / tan(a)) ,
         0, 1, (-w * sin(theta) / tan(a)) + (w * sin(t * v * tan(a) / w + theta) / tan(a)) ,
         0, 0, 1;

    return make_unique<MatrixXd>( F );
}

unique_ptr<MatrixXd> EKFLocalization::calcV(float v, float a, float theta) {

    MatrixXd V(3, 2);
    V <<    t * cos(t * v * tan(a) / w + theta), t * v * (pow(tan(a), 2) + 1) * cos(t * v * tan(a) / w + theta) / tan(a) - w * (-pow(tan(a), 2) - 1) * sin(theta) / pow(tan(a), 2) + w * (-pow(tan(a), 2) - 1) * sin(t * v * tan(a) / w + theta) / pow(tan(a), 2),
            t * sin(t * v * tan(a) / w + theta), t * v * (pow(tan(a), 2) + 1) * sin(t * v * tan(a) / w + theta) / tan(a) + w * (-pow(tan(a), 2) - 1) * cos(theta) / pow(tan(a), 2) - w * (-pow(tan(a), 2) - 1) * cos(t * v * tan(a) / w + theta) / pow(tan(a), 2),
            t * tan(a) / w, t * v * (pow(tan(a), 2) + 1) / w;

    return make_unique<MatrixXd>( V );
}


unique_ptr<MatrixXd> EKFLocalization::calcM(float v) {

    MatrixXd M(2, 2);
    M << this->std_vel * pow(v, 2),   0,
         0,                           pow(this->std_steer, 2);

    return make_unique<MatrixXd>( M );
}


unique_ptr<MatrixXd> EKFLocalization::calcP(const unique_ptr<MatrixXd> &prior_P,
                                            const unique_ptr<MatrixXd> &F,
                                            const unique_ptr<MatrixXd> &V,
                                            const unique_ptr<MatrixXd> &M) {

    MatrixXd P = (*F) * (*prior_P) * F->transpose()  + (*V) * (*M) * V->transpose();

    return make_unique<MatrixXd>( P );
}

#endif










