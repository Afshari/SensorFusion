#include "inc/pf_object.h"

PFObject::PFObject(float x, float y, float theta, QObject *parent) : QObject(parent) {

    this->x = x;
    this->y = y;
    this->theta = theta;
}


PFObject::PFObject(shared_ptr<Vector3d> state, QObject *parent) : QObject(parent) {

    this->x     = (*state)[0];
    this->y     = (*state)[1];
    this->theta = (*state)[2];
}


float PFObject::getX() {

    return this->x;
}

float PFObject::getY() {

    return this->y;
}

float PFObject::getTheta() {

    return this->theta;
}

void PFObject::move(float velocity, float angular_velocity) {

    this->theta += angular_velocity;
    this->x += cos(this->theta) * velocity;
    this->y += sin(this->theta) * velocity;
}


void PFObject::setMeasurements(shared_ptr<vector<Vector2d>> measurements) {

    this->measurements = measurements;
}














