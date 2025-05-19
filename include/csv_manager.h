#ifndef CSV_MANAGER_H
#define CSV_MANAGER_H

#include <Eigen/Dense>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <filesystem>

void readSystemCSV(const std::string& path, Eigen::MatrixXd& A, Eigen::VectorXd& b);
void writeSolutionCSV(const std::string& path, const Eigen::VectorXd& x);

#endif