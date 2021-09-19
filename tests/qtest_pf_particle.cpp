#include "inc/qtest_pf_particle.h"

QTestPFParticle::QTestPFParticle(QObject *parent) : QObject(parent) {

}


void QTestPFParticle::testConstructor() {

    PFParticle particle1(10, 20, 2);
    QVERIFY2( abs( particle1.x - 10 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle1.y - 20 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle1.theta - 2 ) < 1e-4 , "  ");

    QVERIFY2( abs( particle1.velocity_sigma - 0.5 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle1.angular_velocity_sigma - 0.2 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle1.distance_domain - 0.0797884 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle1.angle_domain - 0.7978845 ) < 1e-4 , "  ");


    PFParticle particle2(0, 0, 0);
    QVERIFY2( abs( particle2.x - 0 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle2.y - 0 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle2.theta - 0 ) < 1e-4 , "  ");

    QVERIFY2( abs( particle2.velocity_sigma - 0.5 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle2.angular_velocity_sigma - 0.2 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle2.distance_domain - 0.0797884 ) < 1e-4 , "  ");
    QVERIFY2( abs( particle2.angle_domain - 0.7978845 ) < 1e-4 , "  ");
}


void QTestPFParticle::testUpdateWeight() {

    vector<Vector2d> measurements;
    measurements.push_back( Vector2d(33.261769010906704, 0.8153273463265045) );
    measurements.push_back( Vector2d(76.07751580632818, 1.959386070165502) );
    measurements.push_back( Vector2d(74.63318415532072, 1.6134456361474852) );
    measurements.push_back( Vector2d(27.797911178476532, 0.11717055135509868) );
    measurements.push_back( Vector2d(51.09875346373989,  1.6978888420161173) );

    vector<Vector2d> robot_measurements;
    robot_measurements.push_back( Vector2d(67.28286884668118, 1.1293895583305733) );
    robot_measurements.push_back( Vector2d(65.10275530460008, 2.230390053081443) );
    robot_measurements.push_back( Vector2d(78.27477812219561, 1.9154335173159684) );
    robot_measurements.push_back( Vector2d(69.84522029133024, 0.8166300181512365) );
    robot_measurements.push_back( Vector2d(56.650248840036724, 1.7553265615428595) );

    PFParticle particle;

    for(uint i = 0; i < measurements.size(); i++) {

        float value = 0;
        for(uint j = 0; j < robot_measurements.size(); j++) {
            float dist = particle.pdf(robot_measurements.at(j)[0], measurements.at(i)[0], particle.distance_sigma);
            dist = dist / particle.distance_domain;

            float diff_angle = abs(robot_measurements.at(j)[1] - measurements.at(i)[1]);
            if(diff_angle > M_PI)
                diff_angle = abs(diff_angle - M_PI * 2);
            float angle = particle.pdf(0, diff_angle, particle.angle_sigma);
            angle = angle / particle.angle_domain;

            float v = angle * dist;
            if(v > value)
                value = v;
        }
        particle.weight += value;
    }
    if(measurements.size() == 0)
        return;
    particle.weight /= measurements.size();
    particle.weight = pow(particle.weight, 2);

}





