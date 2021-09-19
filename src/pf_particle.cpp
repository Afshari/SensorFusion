#include "inc/pf_particle.h"

PFParticle::PFParticle(float x, float y, float theta, QObject *parent) : PFObject(x, y, theta, parent) {

    this->weight = 0;
    this->distance_sigma = 5;
    this->angle_sigma = 0.5;
    this->velocity_sigma = 0.3;
    this->angular_velocity_sigma = 0.02;
    this->distance_domain = 0.0797884;
    this->angle_domain = 0.7978845;
}


PFParticle::PFParticle(QObject *parent) : PFParticle(0, 0, 0, parent) {

}

PFParticle::PFParticle(const PFParticle &p) : PFParticle() {

    this->x = p.x;
    this->y = p.y;
    this->theta = p.theta;
    this->weight = p.weight;
}

PFParticle& PFParticle::operator=(const PFParticle& other)
{
    if (this != &other) // not a self-assignment
    {
        this->x = other.x;
        this->y = other.y;
        this->theta = other.theta;
        this->weight = other.weight;
    }
    return *this;
}

void PFParticle::setParams(float x, float y, float theta) {

    this->x = x;
    this->y = y;
    this->theta = theta;
}

float PFParticle::getWeight() {

    return weight;
}

float PFParticle::getVelocitySigma() {

    return velocity_sigma;
}

float PFParticle::getAngularVelocitySigma() {

    return angular_velocity_sigma;
}

void PFParticle::moveParticle(float velocity, float angular_velocity) {

    std::default_random_engine generator;

    std::normal_distribution<float> d_velocity(velocity, this->velocity_sigma);
    velocity = d_velocity(generator);

    std::normal_distribution<float> d_angular_velocity(angular_velocity, this->angular_velocity_sigma);
    angular_velocity = d_angular_velocity(generator);

    this->move(velocity, angular_velocity);
}


void PFParticle::updateWeight(const shared_ptr<vector<Vector2d>>& measurements) {

    for(uint i = 0; i < this->measurements->size(); i++) {

        float max_value = 0;
        for(uint j = 0; j < measurements->size(); j++) {
            float dist = this->pdf(measurements->at(j)[0], this->measurements->at(i)[0], this->distance_sigma) / this->distance_domain;

            float diff_angle = abs(measurements->at(j)[1] - this->measurements->at(i)[1]);
            if(diff_angle > M_PI)
                diff_angle = abs(diff_angle - M_PI * 2);
            float angle = this->pdf(0, diff_angle, this->angle_sigma) / this->angle_domain;

            float cuur_value = angle * dist;
            if(cuur_value > max_value)
                max_value = cuur_value;
        }
        this->weight += max_value;
    }
    if(measurements->size() == 0)
        return;
    this->weight /= measurements->size();
    this->weight = pow(this->weight, 3);

}

double PFParticle::pdf(float x, float mu, float sigma) {

    return stats::dnorm(x, mu, sigma, false);
}








