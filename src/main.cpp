#include "../include/csv_manager.h"
#include "../include/gauss.h"
#include "../include/generator.h"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        if (argc == 5 && std::string(argv[1]) == "--generate") {
            std::size_t n = std::stoul(argv[2]);
            unsigned seed = std::stoul(argv[3]);
            generateRandomSystem(n, seed, argv[4]);
            std::cerr << "Сгенерирована система " << n << "×" << n << " в " << argv[4] << "\n";
            return 0;
        }
        if (argc != 3) {
            std::cerr << "Использование:\n"
                      << "  " << argv[0] << " <input.csv> <output.csv>\n"
                      << "  " << argv[0] << " --generate N SEED <csv>\n";
            return 1;
        }

        Eigen::MatrixXd A;
        Eigen::VectorXd b;
        readSystemCSV(argv[1], A, b);
        Eigen::VectorXd x = gaussSolve(A, b);
        writeSolutionCSV(argv[2], x);
        std::cerr << "Метод Гаусса был применен на матрицу в " << argv[1] << "\n" << "Ответ записан в " << argv[2] << "\n"; 
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 2;
    }
    return 0;
}