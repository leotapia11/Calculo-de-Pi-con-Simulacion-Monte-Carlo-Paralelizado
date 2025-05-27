#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <iomanip>

int main() {
    // 1) Lista de experimentos (igual que tu points_list en Python)
    std::vector<unsigned long long> points_list = {
        10'000'000ULL, 20'000'000ULL, 50'000'000ULL,
        100'000'000ULL, 200'000'000ULL, 500'000'000ULL,
        1'000'000'000ULL, 5'000'000'000ULL, 10'000'000'000ULL
    };

    // 2) Abrimos el fichero CSV y escribimos cabecera
    std::ofstream csv("resultados_secuencial.csv");
    if (!csv) {
        std::cerr << "Error al crear resultados_secuencial.csv\n";
        return 1;
    }
    csv << "total_points,pi_estimate,time_seconds\n";

    // 3) Inicializamos el motor de números aleatorios (Mersenne Twister)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    // 4) Para cada experimento:
    for (auto totalPoints : points_list) {
        unsigned long long countInside = 0;

        // Arrancamos el cronómetro
        auto t0 = std::chrono::high_resolution_clock::now();

        // Tiramos los “dardos”
        for (unsigned long long i = 0; i < totalPoints; ++i) {
            double x = dist(gen);
            double y = dist(gen);
            if (x*x + y*y <= 1.0)
                ++countInside;
        }

        // Detenemos el cronómetro
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = t1 - t0;

        // Estimación de pi
        double piEstimate = 4.0 * double(countInside) / double(totalPoints);

        // 5) Escribimos línea en el CSV
        csv
            << totalPoints << ','
            << std::setprecision(10) << piEstimate << ','
            << elapsed.count() << "\n";

        // Opcional: feedback por pantalla
        std::cout << "Hecho: " << totalPoints
                  << " puntos → π≈" << piEstimate
                  << " en " << elapsed.count() << "s\n";
    }

    csv.close();
    return 0;
}
