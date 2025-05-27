#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void) {
    unsigned long long points_list[] = {
        10000000ULL, 20000000ULL, 50000000ULL,
        100000000ULL, 200000000ULL, 500000000ULL,
        1000000000ULL, 5000000000ULL, 10000000000ULL
    };
    size_t n_experiments = sizeof(points_list) / sizeof(points_list[0]);

    FILE *csv = fopen("resultados_secuencial.csv", "w");
    if (!csv) {
        fprintf(stderr, "Error al crear resultados_secuencial.csv\n");
        return 1;
    }
    fprintf(csv, "total_points,pi_estimate,time_seconds\n");

    srand((unsigned)time(NULL));

    for (size_t i = 0; i < n_experiments; ++i) {
        unsigned long long totalPoints = points_list[i];
        unsigned long long countInside = 0;

        clock_t t0 = clock();

        for (unsigned long long j = 0; j < totalPoints; ++j) {
            double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
            if (x*x + y*y <= 1.0)
                ++countInside;
        }

        clock_t t1 = clock();
        double elapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;
        double piEstimate = 4.0 * (double)countInside / (double)totalPoints;

        fprintf(csv, "%llu,%.10f,%.6f\n", totalPoints, piEstimate, elapsed);
        printf("Hecho: %llu puntos → π≈%.10f en %.6f s\n", totalPoints, piEstimate, elapsed);
    }

    fclose(csv);
    return 0;
}
