%%writefile pi_secuencial.cpp
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <total_points>\n";
        return 1;
    }

    unsigned long long totalPoints = std::stoull(argv[1]);
    unsigned long long countInside = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned long long i = 0; i < totalPoints; i++) {
        double x = dist(gen);
        double y = dist(gen);
        if (x * x + y * y <= 1.0) {
            countInside++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    double piEstimate = 4.0 * static_cast<double>(countInside) / totalPoints;

    std::cout << totalPoints << "," << piEstimate << "," << elapsed.count() << std::endl;

    return 0;
}
