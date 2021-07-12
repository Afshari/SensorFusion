#include "inc/qtest_kf_passive_suspension.h"

QTestKFPassiveSuspension::QTestKFPassiveSuspension(QObject *parent) : QObject(parent) {

}


void QTestKFPassiveSuspension::testLtiDisc_F() {

    MatrixXd ref(4, 4);
    ref << 0.9998,    0.0004,    0.0010,   -0.0010,
           0.0002,    0.9996,    0.0000,    0.0010,
          -0.0437,   -0.0005,    0.9989,    0.0011,
           0.3739,   -0.8856,    0.0098,    0.9897;

    MatrixXd t_A(4, 4);
    t_A <<       0,         0,    1.0000,   -1.0000,
                 0,         0,         0,    1.0000,
          -43.9412,         0,   -1.1263,    1.1263,
          376.0528, -890.0968,    9.6391,   -9.7676;
    shared_ptr<MatrixXd> A = make_shared<MatrixXd>( t_A );

    KFPassiveSuspension suspension;
    float dt = 0.001;
    shared_ptr<MatrixXd> F = suspension.ltiDisc_F(A, dt);

    QVERIFY2(F->isApprox(ref, 1e-4), "  ");
}


void QTestKFPassiveSuspension::testLtiDisc_Q() {

    MatrixXd ref(4, 4);
    ref << 0.0000,    0.0000,   -0.0000,   -0.0000,
           0.0000,    0.2233,   -0.0001,   -0.1276,
          -0.0000,   -0.0001,    0.0000,    0.0000,
          -0.0000,   -0.1276,    0.0000,    0.0875;
    ref = 1e-6 * ref;
    ref = ref.unaryExpr([](double x){return (abs(x)<1e-8)?0.:x;});

    MatrixXd t_A(4, 4);
    t_A <<       0,         0,    1.0000,   -1.0000,
                 0,         0,         0,    1.0000,
          -43.9412,         0,   -1.1263,    1.1263,
          376.0528, -890.0968,    9.6391,   -9.7676;
    shared_ptr<MatrixXd> A = make_shared<MatrixXd>( t_A );
    KFPassiveSuspension suspension;
    float dt = 0.001;
    MatrixXd t_Qc(1, 1);
    t_Qc << 2.2340e-04;
    shared_ptr<MatrixXd> Qc = make_shared<MatrixXd>( t_Qc );
    shared_ptr<VectorXd> L = make_shared<VectorXd>( Vector4d( 0, -1.0000, 0, 0.1285 )  );

    shared_ptr<MatrixXd> Q = suspension.ltiDisc_Q(A, L, Qc, dt);
    Q = make_shared<MatrixXd>( Q->unaryExpr([](double x){return (abs(x)<1e-8)?0.:x;}) );


    QVERIFY2(Q->isApprox(ref, 1e-4), "  ");
}


void QTestKFPassiveSuspension::testPredict() {

    Vector4d ref_x( -19.9209118,   -8.63996359,  57.37623886, 106.7661835 );

    KFPassiveSuspension suspension;

    suspension.x = make_shared<Vector4d>( Vector4d( -19.87092819,  -8.7468581,   56.44568757, 107.00571172 ) );

    MatrixXd t_P(4, 4);
    t_P << 1.20123548e-07,  3.22008851e-07, -1.74187938e-07, -7.85690194e-06,
           3.22008851e-07,  4.87621894e-06, -3.47648886e-07, -5.13354639e-05,
          -1.74187938e-07, -3.47648886e-07,  1.53978360e-06,  9.70202154e-06,
          -7.85690194e-06, -5.13354639e-05,  9.70202154e-06,  8.70548962e-04;
    suspension.P = make_shared<MatrixXd>( t_P );

    suspension.predict();

    QVERIFY2(suspension.x->isApprox(ref_x, 1e-4), "  ");
}


void QTestKFPassiveSuspension::testUpdate_1() {

    Vector4d ref_x( -26.35912618, -12.34415419, 130.12046332, 114.68371551 );

    KFPassiveSuspension suspension;

    suspension.x = make_shared<Vector4d>( Vector4d( -26.31506731, -12.31076066, 130.04864341, 113.147455755 ) );

    MatrixXd t_P(4, 4);
    t_P <<  6.87481157e-08,  5.21062438e-08, -1.12065612e-07, -2.39713295e-06,
            5.21062438e-08,  3.92864018e-07, -3.97152699e-08, -5.76981182e-06,
           -1.12065612e-07, -3.97152699e-08,  1.42395914e-06,  3.32492513e-06,
           -2.39713295e-06, -5.76981182e-06,  3.32492513e-06,  1.61811052e-04;
    suspension.P = make_shared<MatrixXd>( t_P );

    VectorXd t_z ( 1 );
    t_z << -27;

    unique_ptr<VectorXd> z = make_unique<VectorXd>( t_z );
    suspension.update( z );

    QVERIFY2(suspension.x->isApprox(ref_x, 1e-4), "  ");
}

void QTestKFPassiveSuspension::testUpdate_2() {

    Vector4d ref_x( -32.3227836,  -10.67079103, -78.69531955, -51.21634435 );

    KFPassiveSuspension suspension;

    suspension.x = make_shared<Vector4d>( Vector4d( -32.27614212, -10.63519708, -78.76173833, -52.83574217 ) );

    MatrixXd t_P(4, 4);
    t_P <<  6.88723349e-08,  5.25591970e-08, -9.80761578e-08, -2.39125606e-06,
            5.25591970e-08,  3.94515669e-07,  1.12959353e-08, -5.74838229e-06,
           -9.80761578e-08,  1.12959353e-08,  2.99943945e-06,  3.98677601e-06,
           -2.39125606e-06, -5.74838229e-06,  3.98677601e-06,  1.62089092e-04;
    suspension.P = make_shared<MatrixXd>( t_P );

    VectorXd t_z ( 1 );
    t_z << -33;

    unique_ptr<VectorXd> z = make_unique<VectorXd>( t_z );
    suspension.update( z );

    QVERIFY2(suspension.x->isApprox(ref_x, 1e-4), "  ");
}




void QTestKFPassiveSuspension::testStep() {

    Vector4d ref_x( -32.3227836,  -10.67079103, -78.69531955, -51.21634435 );

    KFPassiveSuspension suspension;

    suspension.x = make_shared<Vector4d>( Vector4d( -32.24802149, -10.58383162, -80.21106048, -49.88217787 ) );

    MatrixXd t_P(4, 4);
    t_P <<  6.44344840e-08,  4.91722166e-08, -9.17676558e-08, -2.23718132e-06,
            4.91722166e-08,  3.91929849e-07,  1.60763214e-08, -5.63081667e-06,
           -9.17676558e-08,  1.60763214e-08,  2.98911586e-06,  3.76678011e-06,
           -2.23718132e-06, -5.63081667e-06,  3.76678011e-06,  1.56739174e-04;
    suspension.P = make_shared<MatrixXd>( t_P );

    suspension.predict();

    VectorXd t_z ( 1 );
    t_z << -33;

    unique_ptr<VectorXd> z = make_unique<VectorXd>( t_z );
    suspension.update( z );

    QVERIFY2(suspension.x->isApprox(ref_x, 1e-4), "  ");

}





