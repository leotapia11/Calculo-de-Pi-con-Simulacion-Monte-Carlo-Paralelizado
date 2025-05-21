#include <iostream>
#include <random>

int main() {
    const unsigned long long totalPoints = 500000000ULL;
    unsigned long long countInside = 0;


    std::random_device rd;                      
    std::mt19937 gen(rd());                       
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (unsigned long long i = 0; i < totalPoints; i++) {
        double x = dist(gen);
        double y = dist(gen);
        if (x * x + y * y <= 1.0) {
            countInside++;
        }
    }

    double piEstimate = 4.0 * static_cast<double>(countInside) / totalPoints;

    std::cout << "Total de puntos: " << totalPoints << std::endl;
    std::cout << "Puntos dentro del círculo: " << countInside << std::endl;
    std::cout << "Estimación de Pi: " << piEstimate << std::endl;

    return 0;
}
