#include "inc/pf_localization.h"

PFLocalization::PFLocalization(const shared_ptr<PFRobot> &robot, QObject *parent) : QObject(parent) {

    this->robot = robot;
    particles.resize(100);
}

void PFLocalization::setRobotParam(const shared_ptr<Vector3d> &state) {

    this->robot->setParams(state);
}

void PFLocalization::setRobotMeasurements(shared_ptr<vector<Vector2d>> measurements) {

    this->robot->setMeasurements(measurements);
}

void PFLocalization::robotMove(float velocity, float angular_velocity) {

    this->robot->move(velocity, angular_velocity);
}

void PFLocalization::setParticleMeasurements(int idx, shared_ptr<vector<Vector2d>> measurements) {

    this->particles.at(idx).setMeasurements(measurements);
}

void PFLocalization::updateParticleWeight(int idx, shared_ptr<vector<Vector2d>> measurements) {

    this->particles.at(idx).updateWeight(measurements);
}

void PFLocalization::predictParticle(int idx, float velocity, float angular_velocity) {

    this->particles.at(idx).moveParticle(velocity, angular_velocity);
}

uint PFLocalization::numberOfParticles() {

    return this->particles.size();
}

void PFLocalization::generateParticles() {

    for(uint i = 0; i < particles.size(); i++) {

        float x = stats::runif(0, 30);
        float y = stats::runif(0, 30);
        float theta = stats::runif(0.0f, M_PI * 2);
        particles.at(i).setParams(x, y, theta);
    }
}

string PFLocalization::getAllStateString() {

    std::stringstream stringStream;
    //    stringStream.precision(2);
    stringStream << robot->getX() << "," << robot->getY() << "," << robot->getTheta() << ":";
    for(uint i = 0; i < particles.size(); i++) {
        if(i > 0)
            stringStream << ";";
        stringStream << std::setprecision(3) << particles.at(i).getX() << "," << particles.at(i).getY() << "," << particles.at(i).getTheta();
    }

    return stringStream.str();
}

void PFLocalization::resample() {

    vector<float> weights(particles.size());
    float weights_sum = 0;
    for(uint i = 0; i < particles.size(); i++) {
        weights.at(i) = particles.at(i).getWeight();
        weights_sum += particles.at(i).getWeight();
    }

    float coeff = std::clamp<float>(particles.size() / (weights_sum * 10), 0, 10);
    std::cout << "scale " << coeff << std::endl;
//    if(scale > 10)
//        scale = 10;

    std::default_random_engine generator;
    std::discrete_distribution<float> distribution(weights.begin(), weights.end());
    std::normal_distribution<float> rnd_velocity(0, particles.at(0).getVelocitySigma() * coeff);
    std::normal_distribution<float> rnd_angle(0, particles.at(0).getAngularVelocitySigma() * coeff / 2);

    vector<PFParticle> new_particles;

    for (uint i = 0; i < particles.size(); i++) {
        int idx = distribution(generator);
        float x = particles.at(idx).getX() + rnd_velocity(generator);
        float y = particles.at(idx).getY() + rnd_velocity(generator);
        float theta = particles.at(idx).getTheta() + rnd_angle(generator);
        new_particles.push_back( PFParticle(x, y, theta) );
    }

    std::copy(new_particles.begin(), new_particles.end(), particles.begin());
}






