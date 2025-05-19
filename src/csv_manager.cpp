#include "../include/csv_manager.h"

static std::vector<double> splitLine(const std::string& line) {
    std::vector<double> res;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        try {
            res.push_back(std::stod(cell));
        } catch (const std::exception& e) {
            throw std::runtime_error("Ошибка при разборе числа: " + cell);
        }
    }
    return res;
}

void readSystemCSV(const std::string& path, Eigen::MatrixXd& A, Eigen::VectorXd& b) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Файл не существует: " + path);
    }

    std::ifstream file;
    file.exceptions(std::ios::badbit);
    try {
        file.open(path);
    } catch (const std::ios_base::failure& e) {
        throw std::runtime_error("Не получилось открыть этот файл для чтения: " + path);
    }

    std::string line;
    std::vector<std::vector<double>> rows;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                rows.push_back(splitLine(line));
            } catch (const std::exception& e) {
                throw std::runtime_error("Ошибка в строке " + std::to_string(rows.size() + 1) + ": " + e.what());
            }
        }
    }
    if (rows.empty()) throw std::runtime_error("Пустой CSV: " + path);

    const std::size_t n = rows.size();
    if (rows[0].size() != n + 1)
        throw std::runtime_error("Ожидается " + std::to_string(n + 1) + " столбцов");

    A.resize(n, n);
    b.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        if (rows[i].size() != n + 1)
            throw std::runtime_error("Неверное число столбцов в строке " + std::to_string(i + 1));
        for (std::size_t j = 0; j < n; ++j) A(i, j) = rows[i][j];
        b(i) = rows[i].back();
    }
}

void writeSolutionCSV(const std::string& path, const Eigen::VectorXd& x) {
    std::filesystem::path filePath(path);
    if (filePath.has_parent_path() && !std::filesystem::exists(filePath.parent_path())) {
        throw std::runtime_error("Данного пути не существует: " + filePath.parent_path().string());
    }

    std::ofstream file;
    file.exceptions(std::ios::badbit);
    try {
        file.open(path);
    } catch (const std::ios_base::failure& e) {
        throw std::runtime_error("Не получилось открыть этот файл для записи: " + path);
    }

    for (Eigen::Index i = 0; i < x.size(); ++i) {
        file << x(i);
        if (i + 1 != x.size()) file << ',';
    }
    file << '\n';
    
    if (!file.good()) {
        throw std::runtime_error("Ошибка при записи в файл: " + path);
    }
}