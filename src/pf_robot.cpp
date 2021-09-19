#include "inc/pf_robot.h"

PFRobot::PFRobot(QObject *parent) : PFObject(0, 0, 0, parent) {

}


PFRobot::PFRobot(float x, float y, float theta, QObject *parent) : PFObject(x, y, theta, parent) {


}

PFRobot::PFRobot(shared_ptr<Vector3d> state, QObject *parent) : PFObject(state, parent) {

}


void PFRobot::setParams(const shared_ptr<Vector3d> &state) {

    this->x     = (*state)[0];
    this->y     = (*state)[1];
    this->theta = (*state)[2];
}

