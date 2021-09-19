#include "inc/qtest_pf_object.h"

QTestPFObject::QTestPFObject(QObject *parent) : QObject(parent) {

}


void QTestPFObject::testMove() {

    PFObject obj1(10, 10, 0);
    obj1.move(5, 0);
    QVERIFY2( abs( obj1.x - 15 ) < 1e-4 , "  ");
    QVERIFY2( abs( obj1.y - 10 ) < 1e-4 , "  ");
    QVERIFY2( abs( obj1.theta - 0 ) < 1e-4 , "  ");


    PFObject obj2(48.381, 28.56, 4.37);
    obj2.move(4.11, -0.036);
    QVERIFY2( abs( obj2.x - 46.89 ) < 1e-1 , "  ");
    QVERIFY2( abs( obj2.y - 24.73 ) < 1e-1 , "  ");
    QVERIFY2( abs( obj2.theta - 4.34 ) < 1e-1 , "  ");


    PFObject obj3(13.96, 20.01, -0.54);
    obj3.move(5.23, 0.057);
    QVERIFY2( abs( obj3.x - 18.58 ) < 1e-1 , "  ");
    QVERIFY2( abs( obj3.y - 17.55 ) < 1e-1 , "  ");
    QVERIFY2( abs( obj3.theta - -0.48 ) < 1e-1 , "  ");


    PFObject obj4(-2.62, 76.47, -3.99);
    obj4.move(5.35, -0.045);
    QVERIFY2( abs( obj4.x + 5.94 ) < 1e-1 , "  ");
    QVERIFY2( abs( obj4.y - 80.67 ) < 1e-1 , "  ");
    QVERIFY2( abs( obj4.theta + 4.04 ) < 1e-1 , "  ");
}











