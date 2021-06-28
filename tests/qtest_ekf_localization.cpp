#include "inc/qtest_ekf_localization.h"

QTestEKFLocalization::QTestEKFLocalization(QObject *parent) : QObject(parent) {

}


void QTestEKFLocalization::testConstructor() {

    EKFLocalization ekf(0.1, 0.5, 0.1, 0.1);

    QVERIFY(ekf.x->rows() == 3 && ekf.x->cols() == 1);
    QVERIFY(ekf.P->rows() == 3 && ekf.P->cols() == 3);
    QVERIFY(ekf.F->rows() == 3 && ekf.F->cols() == 3);
    QVERIFY(ekf.R->rows() == 2 && ekf.R->cols() == 2);
    QVERIFY(ekf.Q->rows() == 3 && ekf.Q->cols() == 3);
    QVERIFY(ekf.y->rows() == 2 && ekf.y->cols() == 1);

}

void QTestEKFLocalization::testResidual() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    unique_ptr<VectorXd> ref = make_unique<VectorXd>( Vector2d( { 0.03394354, -0.0464792 } ) );
    unique_ptr<VectorXd> a   = make_unique<VectorXd>( Vector2d( { 43.818,        0.238 } ) );
    unique_ptr<VectorXd> b   = make_unique<VectorXd>( Vector2d( { 43.78405646,   31.70040573 } ) );
    unique_ptr<VectorXd> res = ekf.residual(a, b);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");


    ref = make_unique<VectorXd>( Vector2d( { -0.26831728,   -0.03546623 } ) );
    a   = make_unique<VectorXd>( Vector2d( { 35.133,        0.732 } ) );
    b   = make_unique<VectorXd>( Vector2d( { 35.40131728,   32.18339277 } ) );
    res = ekf.residual(a, b);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");

    ref = make_unique<VectorXd>( Vector2d( { -0.26221709,   -0.03021161 } ) );
    a   = make_unique<VectorXd>( Vector2d( { 38.208,        0.724 } ) );
    b   = make_unique<VectorXd>( Vector2d( { 38.47021709,   32.17013814 } ) );
    res = ekf.residual(a, b);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");

}

void QTestEKFLocalization::testHJacobian() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    MatrixXd m(2, 3);
    m << -0.56192236, -0.82718998,  0., 0.01889249, -0.01283395, -1.;
    unique_ptr<MatrixXd> ref = make_unique<MatrixXd>( m );
    unique_ptr<VectorXd> x   = make_unique<VectorXd>( Vector3d( { -13.6032405, -20.21773263, -30.72631734 } ) );
    unique_ptr<VectorXd> landmark = make_unique<VectorXd>( Vector2d( { 11, 16 } ) );
    unique_ptr<MatrixXd> res = ekf.HJacobian(x, landmark);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");


    m << -0.10193153, -0.99479142,  0., 0.02810041, -0.00287931, -1.;
    ref = make_unique<MatrixXd>( m );
    x   = make_unique<VectorXd>( Vector3d( { -13.60851057, -20.21692656, -30.71470532 } ) );
    landmark = make_unique<VectorXd>( Vector2d( { -10,  15 } ) );
    res = ekf.HJacobian(x, landmark);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");


    m << -0.45036721, -0.89284342,  0., 0.15369142, -0.07752488, -1.;
    ref = make_unique<MatrixXd>( m );
    x   = make_unique<VectorXd>( Vector3d( { -13.61632959, -20.18681779, -30.71201017 } ) );
    landmark = make_unique<VectorXd>( Vector2d( { -11, -15 } ) );
    res = ekf.HJacobian(x, landmark);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");

}



void QTestEKFLocalization::testHx() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    unique_ptr<VectorXd> ref = make_unique<VectorXd>( Vector2d( { 43.78405646, 31.70040573 } ) );
    unique_ptr<VectorXd> x   = make_unique<VectorXd>( Vector3d( { -13.6032405, -20.21773263, -30.72631734 } ) );
    unique_ptr<VectorXd> landmark = make_unique<VectorXd>( Vector2d( { 11, 16 } ) );
    unique_ptr<VectorXd> res = ekf.Hx(x, landmark);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");


    ref = make_unique<VectorXd>( Vector2d( { 36.38969007, 32.17870607 } ) );
    x   = make_unique<VectorXd>( Vector3d( { -13.61276245, -20.20990874, -30.7073534 } ) );
    landmark = make_unique<VectorXd>( Vector2d( { -10,  16 } ) );
    res = ekf.Hx(x, landmark);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");


    ref = make_unique<VectorXd>( Vector2d( { 5.43190142, 31.96838902 } ) );
    x   = make_unique<VectorXd>( Vector3d( { -13.62398805, -20.18345598, -30.7012082 } ) );
    landmark = make_unique<VectorXd>( Vector2d( { -12, -15 } ) );
    res = ekf.Hx(x, landmark);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");
}


void QTestEKFLocalization::testMove() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    unique_ptr<VectorXd> ref = make_unique<VectorXd>( Vector3d( { -20.18120416, -12.07864027, 29.84808727 } ) );
    unique_ptr<VectorXd> x   = make_unique<VectorXd>( Vector3d( { -20.33603814, -9.67268248,  31.35461782 } ) );
    unique_ptr<VectorXd> u = make_unique<VectorXd>( Vector2d( { 24.10934771, -1.50653054 } ) );
    unique_ptr<VectorXd> res = ekf.move(x, u);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");


    ref = make_unique<VectorXd>( Vector3d( { -13.93197419, -20.13896966, 32.5359183 } ) );
    x   = make_unique<VectorXd>( Vector3d( { -16.37744233, -20.30090509, 32.46979625 } ) );
    u   = make_unique<VectorXd>( Vector2d( { 24.50823842,  0.06612205 } ) );
    res = ekf.move(x, u);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");


    ref = make_unique<VectorXd>( Vector3d( { -5.52721469, -19.36541078, 32.81518997 } ) );
    x   = make_unique<VectorXd>( Vector3d( { -8.02600925, -19.38111513, 32.80890529 } ) );
    u   = make_unique<VectorXd>( Vector2d( { 2.49884390e+01, 6.28468591e-03 } ) );
    res = ekf.move(x, u);
    QVERIFY2(ref->isApprox(*res, 1e-4), "  ");
}


void QTestEKFLocalization::testPredict() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    /*********************/
    /*******Test 1********/
    /*********************/

    unique_ptr<VectorXd> prior_x = make_unique<VectorXd>( Vector3d( { -18.13236483, 13.19801501, 37.93045011 } ) );
    unique_ptr<VectorXd> u = make_unique<VectorXd>( Vector2d( { 19.39568599,  0.80476266 } ) );
    MatrixXd prior_P(3, 3);
    prior_P <<  6.39011755e-04, -8.38867162e-05, -3.79601249e-05,
                -8.38867163e-05,  8.11039663e-04,  2.02738186e-05,
                -3.79601249e-05,  2.02738186e-05,  5.84228171e-04;

    unique_ptr<VectorXd> post_x = make_unique<VectorXd>( Vector3d( { -16.78769625, 14.59579638, 38.73521277 } ) );
    MatrixXd post_P(3, 3);
    post_P <<  28.68526748,  16.40539471, -68.70906415,
               16.40539471,   9.38484172, -39.29834311,
               -68.70906415, -39.29834311, 164.58392743;

    ekf.x = std::move( prior_x );
    ekf.P = make_unique<MatrixXd>( prior_P );

    ekf.predict(u);

    QVERIFY2(post_x->isApprox(*ekf.x, 1e-4), "  ");
    QVERIFY2(post_P.isApprox(*ekf.P, 3), "  ");


    /*********************/
    /*******Test 2********/
    /*********************/

    prior_x = make_unique<VectorXd>( Vector3d( { -13.04816041, 15.86104942, 38.97347574 } ) );
    u = make_unique<VectorXd>( Vector2d( { 2.02493464e+01, 1.32699273e-03 } ) );
    prior_P <<  9.27716513e-03,  1.88274430e-03, -7.74115245e-05,
                1.88274430e-03,  7.42576214e-03,  1.33114192e-04,
                -7.74115245e-05,  1.33114192e-04,  2.85291026e-04;

    post_x = make_unique<VectorXd>( Vector3d( { -11.02322755, 15.8637365, 38.97480273 } ) );
    post_P <<  50.30494573, -3.20393432, -4.86863738,
               -3.20393432, 42.04391507,  1.40413125,
               -4.86863738,  1.40413125,  0.50019234;

    ekf.x = std::move( prior_x );
    ekf.P = make_unique<MatrixXd>( prior_P );

    ekf.predict(u);

    QVERIFY2(post_x->isApprox(*ekf.x, 1e-4), "  ");
    QVERIFY2(post_P.isApprox(*ekf.P, 3), "  ");


    /*********************/
    /*******Test 3********/
    /*********************/

    prior_x = make_unique<VectorXd>( Vector3d( { -6.9511443, 15.20605592, 39.14969028 } ) );
    u = make_unique<VectorXd>( Vector2d( { 2.04466809e+01, 4.51869340e-03 } ) );
    prior_P <<  0.00854055,  0.00117841, -0.00043846,
                0.00117841,  0.00849199,  0.00013272,
                -0.00043846,  0.00013272,  0.00025585;

    post_x = make_unique<VectorXd>( Vector3d( { -4.90649708, 15.21529512, 39.15420897 } ) );
    post_P <<  53.47151251, -2.48481833, -5.23465806,
               -2.48481833, 41.61911636,  0.33816067,
               -5.23465806,  0.33816067,  0.51309291;

    ekf.x = std::move( prior_x );
    ekf.P = make_unique<MatrixXd>( prior_P );

    ekf.predict(u);

    QVERIFY2(post_x->isApprox(*ekf.x, 1e-4), "  ");
    QVERIFY2(post_P.isApprox(*ekf.P, 3), "  ");

}


void QTestEKFLocalization::testUpdate() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);
    ekf.setR(0.3, 0.1);

    /*********************/
    /*******Test 1********/
    /*********************/

    unique_ptr<VectorXd> prior_x = make_unique<VectorXd>( Vector3d( { 11.99960625,  16.91019943, -11.00267899 } ) );
    unique_ptr<VectorXd> z = make_unique<VectorXd>( Vector2d( { 1.333, -4.007 } ) );
    unique_ptr<VectorXd> landmark = make_unique<VectorXd>( Vector2d( { 11, 16 } ) );
    MatrixXd prior_P(3, 3);
    prior_P <<  0.02877158,  0.00497821, -0.00231896,
                0.00497821,  0.01596295, -0.00138645,
               -0.00231896, -0.00138645,  0.00075289;

    unique_ptr<VectorXd> post_x = make_unique<VectorXd>( Vector3d( { 12.01460289, 16.89122615, -11.00141577 } ) );
    MatrixXd post_P(3, 3);
    post_P <<  0.01946433,  0.00562709, -0.00195027,
               0.00562709,  0.01097789, -0.0009004 ,
              -0.00195027, -0.0009004,   0.00068527;

    ekf.x = std::move( prior_x );
    ekf.P = make_unique<MatrixXd>( prior_P );

    ekf.update(z, landmark);

    QVERIFY2(post_x->isApprox(*ekf.x, 1), "  ");
    QVERIFY2(post_P.isApprox(*ekf.P, 1), "  ");


    /*********************/
    /*******Test 2********/
    /*********************/

    prior_x = make_unique<VectorXd>( Vector3d( { 12.08909731, 16.93531182, -11.02380838 } ) );
    z = make_unique<VectorXd>( Vector2d( { 22.153, 1.586 } ) );
    landmark = make_unique<VectorXd>( Vector2d( { -10, 18 } ) );
    prior_P <<  0.01129495,  0.0028737,  -0.00096387,
                0.0028737,   0.00992481, -0.00048254,
               -0.00096387, -0.00048254,  0.00050623;

    post_x = make_unique<VectorXd>( Vector3d( { 12.09660523, 16.939215 , -11.02587416 } ) );
    post_P <<  0.00997099,  0.00252346, -0.00081099,
               0.00252346,  0.00978947, -0.0004154,
              -0.00081099, -0.0004154,   0.00047188;

    ekf.x = std::move( prior_x );
    ekf.P = make_unique<MatrixXd>( prior_P );

    ekf.update(z, landmark);

    QVERIFY2(post_x->isApprox(*ekf.x, 1), "  ");
    QVERIFY2(post_P.isApprox(*ekf.P, 1), "  ");


    /*********************/
    /*******Test 3********/
    /*********************/

    prior_x = make_unique<VectorXd>( Vector3d( { 12.08738074, 16.92199845, -11.03041289 } ) );
    z = make_unique<VectorXd>( Vector2d( { 39.864, -3.64 } ) );
    landmark = make_unique<VectorXd>( Vector2d( { -12, -15 } ) );
    prior_P <<  0.00802676,  0.0010853,  -0.00057167,
                0.0010853,   0.00815833, -0.0002195,
               -0.00057167, -0.0002195,   0.00040125;

    post_x = make_unique<VectorXd>( Vector3d( { 12.08448916, 16.91598572, -11.03403059 } ) );
    post_P <<  0.00768369,  0.0006624,  -0.00052682,
               0.0006624,   0.00763268, -0.00017129,
              -0.00052682, -0.00017129,  0.00038385;

    ekf.x = std::move( prior_x );
    ekf.P = make_unique<MatrixXd>( prior_P );

    ekf.update(z, landmark);

    QVERIFY2(post_x->isApprox(*ekf.x, 1), "  ");
    QVERIFY2(post_P.isApprox(*ekf.P, 1), "  ");



}


void QTestEKFLocalization::testCalcF() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    float v = 24.99795;
    float a = -0.0961403;
    float theta = 45.0174083;

    unique_ptr<MatrixXd> res_F = ekf.calcF(v, a, theta);
    MatrixXd ref_F(3, 3);
    ref_F << 1.,         0.,         6.790179521,
             0.,         1.,         1.34227304,
             0.,         0.,         1.;
    QVERIFY2(res_F->isApprox(ref_F, 1e-4), "  ");



    v = 25.499073;
    a = -0.0965152;
    theta = 45.279974;

    res_F = ekf.calcF(v, a, theta);
    ref_F << 1.,         0.,         5.92978041,
             0.,         1.,         2.50535629,
             0.,         0.,         1.;
    QVERIFY2(res_F->isApprox(ref_F, 1e-4), "  ");



    v = 25.0810711;
    a = -0.09651879;
    theta = 45.289845;

    res_F = ekf.calcF(v, a, theta);
    ref_F << 1.,         0.,         6.085112221,
             0.,         1.,         2.93947878,
             0.,         0.,         1.;
    QVERIFY2(res_F->isApprox(ref_F, 1e-4), "  ");
}



void QTestEKFLocalization::testCalcV() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    float v = 24.99795;
    float a = -0.0961403;
    float theta = 45.0174083;


    unique_ptr<MatrixXd> res_V = ekf.calcV(v, a, theta);
    MatrixXd ref_V(3, 2);
    ref_V << -7.99228214e-01,  2.23145482e+02,
              6.01027671e-01,  -2.28308259e+02,
             -1.92875393e-01,   5.04608808e+01;
    QVERIFY2(res_V->isApprox(ref_V, 1e-4), "  ");



    v = 25.499073;
    a = -0.0965152;
    theta = 45.279974;

    res_V = ekf.calcV(v, a, theta);
    ref_V << -8.78459401e-01,  2.59654357e+02,
              4.77816995e-01, -1.88847422e+02,
             -1.93632051e-01,  5.14761707e+01;
    QVERIFY2(res_V->isApprox(ref_V, 1e-4), "  ");



    v = 25.0810711;
    a = -0.09651879;
    theta = 45.289845;

    res_V = ekf.calcV(v, a, theta);
    ref_V << -9.18098894e-01,  2.70707397e+02,
              3.96351386e-01, -1.67076209e+02,
             -1.93639278e-01,  5.06323643e+01;
    QVERIFY2(res_V->isApprox(ref_V, 1e-4), "  ");
}


void QTestEKFLocalization::testCalcM() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    float v = 24.99795372056359;

    MatrixXd ref_M(2, 2);
    ref_M <<  6.2489769e+01, 0.0000000e+00,
              0.0000000e+00, 3.0461742e-04;
    unique_ptr<MatrixXd> res_M = ekf.calcM(v);
    QVERIFY2(res_M->isApprox(ref_M, 1e-4), "  ");



    v = 25.499073773952905;
    ref_M << 6.50202763e+01, 0.00000000e+00,
             0.00000000e+00, 3.04617420e-04;
    res_M = ekf.calcM(v);
    QVERIFY2(res_M->isApprox(ref_M, 1e-4), "  ");


    v = 25.081071118731998;
    ref_M << 6.29060128e+01, 0.00000000e+00,
             0.00000000e+00, 3.04617420e-04;
    res_M = ekf.calcM(v);
    QVERIFY2(res_M->isApprox(ref_M, 1e-4), "  ");
}


void QTestEKFLocalization::testCalcP() {

    EKFLocalization ekf(1.0, 0.5, 0.1, 0.1);

    MatrixXd F(3, 3);
    F << 1.,          0.,         -0.01899789,
         0.,          1.,          0.00546351,
         0.,          0.,          1.;
    MatrixXd V(3, 2);
    V << 4.91009927e-01, -1.15035064e+02,
         8.71153977e-01, -2.03986610e+02,
         -2.33825188e+01,  5.48118054e+03;
    MatrixXd M(2, 2);
    M << 3.96197304e+01, 0.00000000e+00,
         0.00000000e+00, 3.04617420e-04;
    MatrixXd prior_P(3, 3);
    prior_P <<  9.81886546e-04,  1.29638198e-04, -2.24892815e-05,
                1.29638198e-04,  9.42017369e-04, -2.29081163e-05,
                -2.24892815e-05, -2.29081163e-05,  5.88541524e-04;
    MatrixXd ref_P(3, 3);
    ref_P << 1.35839558e+01,  2.40953159e+01, -6.46945894e+02,
             2.40953159e+01,  4.27440162e+01, -1.14763390e+03,
             -6.46945894e+02, -1.14763390e+03,  3.08135034e+04;
    unique_ptr<MatrixXd> P = ekf.calcP( make_unique<MatrixXd>(prior_P),
                                        make_unique<MatrixXd>(F),
                                        make_unique<MatrixXd>(V),
                                        make_unique<MatrixXd>(M) );
    QVERIFY2(P->isApprox(ref_P, 1e-4), "  ");




    F << 1.,          0.,         -1.83524551,
         0.,          1.,         -3.84211287,
         0.,          0.,          1.;
    V << -0.4431038,  -22.57456896,
         -0.89647031, -88.84421158,
          0.46966954,  42.22617372;
    M << 4.00384474e+01, 0.00000000e+00,
         0.00000000e+00, 3.04617420e-04;
    prior_P <<  8.42004601e-04,  1.27405934e-05, -2.58090108e-04,
                1.27405995e-05,  1.93859731e-03,  1.72664034e-04,
                -2.58090109e-04,  1.72664034e-04,  5.50280273e-04;
    ref_P << 8.02006706,  16.51996285,  -8.6241365,
             16.51996285,  34.59042925, -18.0027095,
             -8.6241365,  -18.0027095,   9.37575851;

    P = ekf.calcP( make_unique<MatrixXd>(prior_P),
                    make_unique<MatrixXd>(F),
                    make_unique<MatrixXd>(V),
                    make_unique<MatrixXd>(M) );

    QVERIFY2(P->isApprox(ref_P, 1e-4), "  ");



    F << 1.,          0.,         -1.17231435,
         0.,          1.,         -0.49061176,
         0.,          0.,          1.;
    V << -0.72226376, -52.09954621,
          0.69161772,  47.43216398,
          0.62835645,  46.81830408;
    M << 4.5394875e+01, 0.0000000e+00,
         0.0000000e+00, 3.0461742e-04;
    prior_P <<  0.00391686,  0.00013354, -0.00019117,
                0.00013354,  0.00576378, -0.00014584,
                -0.00019117, -0.00014584,  0.00053857;
    ref_P << 24.5128619,  -23.42818125, -21.34581802,
             -23.42818125,  22.4053284,  20.40386808,
             -21.34581802,  20.40386808,  18.59158752;

    P = ekf.calcP( make_unique<MatrixXd>(prior_P),
                    make_unique<MatrixXd>(F),
                    make_unique<MatrixXd>(V),
                    make_unique<MatrixXd>(M) );

    QVERIFY2(P->isApprox(ref_P, 1e-4), "  ");
}












