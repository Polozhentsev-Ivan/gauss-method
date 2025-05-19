#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstddef>
#include <string>
#include <fstream>
#include <random>
#include <stdexcept>
#include <Eigen/Dense>

void generateRandomSystem(std::size_t n, unsigned seed, const std::string& outCsv);

#endif