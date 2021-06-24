#include "ekf_localization.h"

EKFLocalization::EKFLocalization(QObject *parent) : QObject(parent) {


    this->dim_x = 3;
    this->dim_z = 2;
    this->dim_u = 2;

}
