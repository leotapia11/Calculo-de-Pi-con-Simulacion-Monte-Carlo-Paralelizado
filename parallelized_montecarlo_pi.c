#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

static double elapsed_sec(double t0, double t1) {
    return t1 - t0;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned long long totals[] = {
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
    int n_totals = sizeof(totals)/sizeof(*totals);

    if (rank == 0) {
        printf("processes,total_points,pi_estimate,elapsed_seconds\n");
        fflush(stdout);
    }

    for (int t = 0; t < n_totals; ++t) {
        unsigned long long total = totals[t];

        unsigned long long base = total / size;
        unsigned long long rest = total % size;
        unsigned long long local_points = base + (rank < rest ? 1 : 0);

        /* Seed per rank */
        unsigned int seed = (unsigned int)(time(NULL) ^ (rank << 16));

        MPI_Barrier(MPI_COMM_WORLD);
        double t0 = MPI_Wtime();

        /* Monte Carlo on local chunk */
        unsigned long long local_inside = 0;
        for (unsigned long long i = 0; i < local_points; ++i) {
            double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
            if (x*x + y*y <= 1.0) ++local_inside;
        }

        /* Reduce counts to rank 0 */
        unsigned long long total_inside = 0;
        MPI_Reduce(&local_inside, &total_inside, 1, MPI_UNSIGNED_LONG_LONG,
                   MPI_SUM, 0, MPI_COMM_WORLD);

        double t1 = MPI_Wtime();
        double secs = elapsed_sec(t0, t1);

        if (rank == 0) {
            double pi = 4.0 * (double)total_inside / (double)total;
            printf("%d,%llu,%.10f,%.6f\n", size, total, pi, secs);
            fflush(stdout);
        }
    }

    MPI_Finalize();
    return 0;
}
