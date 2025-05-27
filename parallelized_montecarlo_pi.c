#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    unsigned long long points;
    unsigned long long inside;
    unsigned int       seed;
} thread_data_t;

static void *worker(void *arg) {
    thread_data_t *td = arg;
    unsigned long long in = 0;
    for (unsigned long long i = 0; i < td->points; ++i) {
        double x = (double)rand_r(&td->seed) / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand_r(&td->seed) / RAND_MAX * 2.0 - 1.0;
        if (x*x + y*y <= 1.0) ++in;
    }
    td->inside = in;
    return NULL;
}

static double elapsed_sec(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) + (b.tv_nsec - a.tv_nsec) / 1e9;
}

int main(void) {
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

    FILE *f = fopen("results.csv", "w");
    if (!f) {
        perror("fopen");
        return EXIT_FAILURE;
    }
    fprintf(f, "threads,total_points,pi_estimate,elapsed_seconds\n");

    for (int threads = 2; threads <= 42; ++threads) {
        for (int t = 0; t < n_totals; ++t) {
            unsigned long long total = totals[t];

            pthread_t *tid = malloc(sizeof(pthread_t)*threads);
            thread_data_t *td = malloc(sizeof(thread_data_t)*threads);

            unsigned long long base = total / threads;
            unsigned long long rest = total % threads;

            for (int i = 0; i < threads; ++i) {
                td[i].points = base + (i < rest);
                td[i].inside = 0;
                td[i].seed   = (unsigned)time(NULL) ^ (i << 16);
                pthread_create(&tid[i], NULL, worker, &td[i]);
            }

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            unsigned long long in_total = 0;
            for (int i = 0; i < threads; ++i) {
                pthread_join(tid[i], NULL);
                in_total += td[i].inside;
            }

            clock_gettime(CLOCK_MONOTONIC, &end);

            double pi = 4.0 * (double)in_total / (double)total;
            double secs = elapsed_sec(start, end);

            fprintf(f, "%d,%llu,%.10f,%.6f\n", threads, total, pi, secs);

            free(tid);
            free(td);
        }
    }

    fclose(f);
    return 0;
}
