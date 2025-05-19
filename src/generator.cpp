#include "../include/generator.h"

void generateRandomSystem(std::size_t n, unsigned seed, const std::string& outCsv) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    Eigen::MatrixXd A(n, n);
    Eigen::VectorXd b(n);
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) A(i, j) = dist(gen);
        b(i) = dist(gen);
    }

    std::ofstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);
    file.open(outCsv);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            file << A(i, j) << ',';
        }
        file << b(i) << '\n';
    }
}