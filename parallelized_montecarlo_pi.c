#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  
#include <time.h>    
#include <mpi.h>      


static inline double elapsed_sec(double t0, double t1) { return t1 - t0; }

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const uint64_t totals[] = {
        10000000ULL,
        20000000ULL,
        50000000ULL,
        100000000ULL,
        200000000ULL,
        500000000ULL,
        1000000000ULL,
        5000000000ULL,
        10000000000ULL
    };
    const int n_totals = sizeof(totals) / sizeof(*totals);

    if (rank == 0) {
        puts("processes,total_points,pi_estimate,elapsed_seconds");
        fflush(stdout);
    }

    /* Bucle sobre los distintos tamaños de muestra */
    for (int t = 0; t < n_totals; ++t) {
        uint64_t total = totals[t];

        /* Distribuir puntos de forma balanceada */
        uint64_t base = total / size;
        uint64_t rest = total % size;
        uint64_t local_points = base + ((uint64_t)rank < rest ? 1 : 0);

        /* Semilla distinta por proceso (suma constante para reproducibilidad) */
        unsigned int seed = (unsigned int)(123456789u + time(NULL) + (rank << 16));

        MPI_Barrier(MPI_COMM_WORLD);          /
        double t0 = MPI_Wtime();


        uint64_t local_inside = 0;
        for (uint64_t i = 0; i < local_points; ++i) {
            double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
            if (x * x + y * y <= 1.0)
                ++local_inside;
        }


        uint64_t total_inside = 0;
        MPI_Reduce(&local_inside, &total_inside, 1,
                   MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

        double secs = elapsed_sec(t0, MPI_Wtime());


        if (rank == 0) {
            double pi_est = 4.0 * (double)total_inside / (double)total;
            printf("%d,%llu,%.10f,%.6f\n",
                   size, (unsigned long long)total, pi_est, secs);
            fflush(stdout);
        }
    }

    MPI_Finalize();
    return 0;
}
