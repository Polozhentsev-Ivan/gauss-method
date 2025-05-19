#ifndef GAUSS_H
#define GAUSS_H
#include <Eigen/Dense>
#include <algorithm>
#include <cmath>
#include <stdexcept>

Eigen::VectorXd gaussSolve(Eigen::MatrixXd A, Eigen::VectorXd b);

#endif