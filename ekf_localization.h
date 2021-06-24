#ifndef EXTENDEDKALMANFILTER_H
#define EXTENDEDKALMANFILTER_H

#include <QObject>
#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;


class EKFLocalization : public QObject
{
    Q_OBJECT
public:
    explicit EKFLocalization(QObject *parent = nullptr);


private:

    VectorXd* x;
    MatrixXd* P;
    MatrixXd* B;
    MatrixXd* F;
    MatrixXd* R;
    MatrixXd* Q;
    VectorXd* y;

    float wheel_base;
    float dt;
    float std_vel;
    float std_steer;

    int dim_x;
    int dim_z;
    int dim_u;

signals:

};

#endif // EXTENDEDKALMANFILTER_H
