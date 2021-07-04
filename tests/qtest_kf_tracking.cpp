#include "inc/qtest_kf_tracking.h"

QTestKFTracking::QTestKFTracking(QObject *parent) : QObject(parent) {

}


void QTestKFTracking::testConstructor() {

    KFTracking kf;
    kf.init( 0, 0, 0.1, 0.1, 0.1, 1 );

    QVERIFY(kf.x->rows() == 4 && kf.x->cols() == 1);
    QVERIFY(kf.P->rows() == 4 && kf.P->cols() == 4);
    QVERIFY(kf.A->rows() == 4 && kf.A->cols() == 4);
    QVERIFY(kf.H->rows() == 2 && kf.H->cols() == 4);
    QVERIFY(kf.Q->rows() == 4 && kf.Q->cols() == 4);
    QVERIFY(kf.R->rows() == 2 && kf.R->cols() == 2);
    QVERIFY(kf._I->rows() == 4 && kf._I->cols() == 4);

    Vector4d x( 0, 0, 0, 0 );
    QVERIFY2(kf.x->isApprox(x, 1e-4), "  ");

    MatrixXd A(4, 4);
    A << 1,     0,      0.1, 	0,
         0,     1,      0, 		0.1,
         0,     0,      1, 		0,
         0,     0,      0,		1;
    QVERIFY2(kf.A->isApprox(A, 1e-4), "  ");

    MatrixXd H(2, 4);
    H << 1, 0, 0, 0,
         0, 1, 0, 0;
    QVERIFY2(kf.H->isApprox(H, 1e-4), "  ");


    MatrixXd Q(4, 4);
    Q <<    2.5e-05, 	0,			5.0e-04,	0,
            0,			2.5e-05,	0, 			5.0e-04,
            5.0e-04,	0,			1.0e-02,	0,
            0,			5.0e-04, 	0, 			1.0e-02;
    QVERIFY2(kf.Q->isApprox(Q, 1e-4), "  ");


    MatrixXd R(2, 2);
    R << 0.01,  	0,
         0,			0.01;
    QVERIFY2(kf.R->isApprox(R, 1e-4), "  ");


    MatrixXd P(4, 4);
    P <<    1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;
    QVERIFY2(kf.P->isApprox(P, 1e-4), "  ");
}


void QTestKFTracking::testPredict() {

    KFTracking kf;
    kf.init( 0, 0, 0.1, 0.1, 0.1, 1 );
    kf.predict();

    Vector4d x ( 0, 0, 0, 0 );
    MatrixXd P(4, 4);
    P <<    1.010025, 	0, 			0.1005, 	0,
            0,          1.010025, 	0, 			0.1005,
            0.1005, 	0, 			1.01, 		0,
            0,          0.1005, 	0, 			1.01;

    QVERIFY2(kf.x->isApprox(x, 1e-4), "  ");
    QVERIFY2(kf.P->isApprox(P, 1e-4), "  ");
}



void QTestKFTracking::testUpdate() {

    KFTracking kf;
    kf.init( 0, 0, 0.1, 0.1, 0.1, 1 );
    kf.predict();

    Vector2d z( 107, 298 );
    kf.update( make_unique<VectorXd>( z ) );

    Vector4d x( 108.07, 300.98, 10.75, 29.94 );
    MatrixXd P(4, 4);
    P <<    -0.0101255,		0.,         	-0.00100751,  0.,
            0.,         	-0.0101255, 	0.,         -0.00100751,
            -0.00100751,  	0.,          	0.99989975,  0.,
            0.,         	-0.00100751,  	0.,          0.99989975;


//    std::cout << *kf.x << std::endl;
//    std::cout << std::endl;
//    std::cout <<     x << std::endl;

    QVERIFY2(kf.x->isApprox(x, 1e-1), "  ");
    QVERIFY2(kf.P->isApprox(P, 1e-1), "  ");
}


















