#include "../include/gauss.h"


Eigen::VectorXd gaussSolve(Eigen::MatrixXd A, Eigen::VectorXd b) {
    const int n = static_cast<int>(A.rows());
    if (A.cols() != n || b.size() != n)
        throw std::invalid_argument("Размеры A и b не согласованы");

    for (int k = 0; k < n; ++k) {
        int p = k;
        double max_val = std::abs(A(k, k));
        for (int i = k + 1; i < n; ++i) {
            double v = std::abs(A(i, k));
            if (v > max_val) { max_val = v; p = i; }
        }
        if (max_val == 0.0) throw std::runtime_error("Матрица вырождена");
        if (p != k) {
            A.row(k).swap(A.row(p));
            std::swap(b(k), b(p));
        }

        const auto pRow = A.row(k);
        for (int i = k + 1; i < n; ++i) {
            double factor = A(i, k) / A(k, k);
            A.row(i) -= factor * pRow;
            b(i)    -= factor * b(k);
        }
    }

    Eigen::VectorXd x(n);
    for (int i = n - 1; i >= 0; --i) {
        double rhs = b(i);
        if (i + 1 < n)
            rhs -= A.row(i).segment(i + 1, n - i - 1).dot(x.segment(i + 1, n - i - 1));
        x(i) = rhs / A(i, i);
    }
    return x;
}