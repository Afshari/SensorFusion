#include "inc/qtest_run_localization.h"

QTestRunLocalization::QTestRunLocalization(QObject *parent) : QObject(parent) {

}

void QTestRunLocalization::testRunStep_1() {

    RunLocalization runLocalization;

    string data = "100:2.0441, 0.0001,0.1,1,0.3,0.1,1.5,0.1,0.1:17.711,-0.553;18.262,-0.599;18.548,-0.480;19.099,-0.547;18.384,0.679;19.222,0.643;20.060,0.631;20.900,0.566;20.435,0.559;18.401,-3.697;19.001,-3.710;19.616,-3.774;20.272,-3.826;14.484,-2.390;15.236,-2.401;16.034,-2.483;16.883,-2.478:10,15;11,15;10,16;11,16;-10,15;-10,16;-10,17;-10,18;-9,18;-10,-15;-11,-15;-12,-15;-13,-15;10,-11;10,-12;10,-13;10,-14";
    shared_ptr<EKFLocalization> ekf = make_shared<EKFLocalization>( 0.1, 0.5, 0.1, 0.1 );
    shared_ptr<InputParser> parser = make_shared<InputParser>();

    runLocalization.step(data, ekf, parser);
}


void QTestRunLocalization::testRunStep_2() {

    RunLocalization runLocalization;

    string data = "100:2.0441, 0.0001,0.1,1,0.3,0.1,1.5,0.1,0.1:17.711,-0.553;18.262,-0.599;18.548,-0.480;19.099,-0.547;18.384,0.679;19.222,0.643;20.060,0.631;20.900,0.566;20.435,0.559;18.401,-3.697;19.001,-3.710;19.616,-3.774;20.272,-3.826;14.484,-2.390;15.236,-2.401;16.034,-2.483;16.883,-2.478:10,15;11,15;10,16;11,16;-10,15;-10,16;-10,17;-10,18;-9,18;-10,-15;-11,-15;-12,-15;-13,-15;10,-11;10,-12;10,-13;10,-14";
    shared_ptr<EKFLocalization> ekf = make_shared<EKFLocalization>( 0.1, 0.5, 0.1, 0.1 );
    shared_ptr<InputParser> parser = make_shared<InputParser>();

    runLocalization.step(data, ekf, parser);


    data = "101:15.1599, 1.5166:29.556,0.070;30.540,0.064;29.617,0.086;30.625,0.136;9.661,0.219;9.911,0.282;10.276,0.416;10.696,0.432;11.594,0.408;29.646,-1.271;29.344,-1.266;29.059,-1.308;28.827,-1.356;38.069,-0.728;38.711,-0.760;39.378,-0.749;40.045,-0.704";

    ekf->x = make_unique<VectorXd>( Vector3d( -19.19779353, 10.74991834, -25.12213237 ) );
    MatrixXd P(3, 3);
    P << 7.57708474e-04, -2.26277282e-05, -4.86407700e-06,
        -2.26277283e-05,  6.43253033e-04, -2.31309836e-05,
        -4.86407700e-06, -2.31309836e-05,  5.89015880e-04;
    ekf->P = make_unique<MatrixXd>( P );

    runLocalization.step(data, ekf, parser);
}

















