#include <gtest/gtest.h>
#include "../include/gauss.h"
#include "../include/generator.h"

TEST(Gauss, Small3x3) {
    Eigen::Matrix<double, 3, 3> A;
    A << 2, 1, -1,
         -3, -1, 2,
         -2, 1, 2;
    Eigen::Vector3d b(8, -11, -3);
    Eigen::Vector3d x = gaussSolve(A, b);

    Eigen::Vector3d expected(2, 3, -1);
    EXPECT_TRUE(x.isApprox(expected, 1e-12));
}

TEST(Gauss, Random100) {
    const std::size_t n = 100;
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    Eigen::MatrixXd A(n, n);
    Eigen::VectorXd b(n);
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) A(i, j) = dist(gen);
        b(i) = dist(gen);
    }

    Eigen::VectorXd x = gaussSolve(A, b);
    Eigen::VectorXd residual = A * x - b;
    EXPECT_LT(residual.norm(), 1e-6);
}