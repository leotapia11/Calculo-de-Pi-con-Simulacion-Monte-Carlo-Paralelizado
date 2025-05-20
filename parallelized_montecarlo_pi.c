#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    unsigned long long points;
    unsigned long long inside;
    unsigned int       seed;
} thread_data_t;

static void *worker(void *arg)
{
    thread_data_t *td = (thread_data_t *)arg;
    unsigned long long in = 0;

    for (unsigned long long i = 0; i < td->points; ++i) {
        double x = (double)rand_r(&td->seed) / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand_r(&td->seed) / RAND_MAX * 2.0 - 1.0;
        if (x * x + y * y <= 1.0) ++in;
    }
    td->inside = in;
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "uso: %s <total_puntos> <hilos>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long long total = strtoull(argv[1], NULL, 10);
    int threads = atoi(argv[2]);
    if (threads < 1) threads = 1;

    pthread_t       *tid = malloc(sizeof(pthread_t) * threads);
    thread_data_t   *td  = malloc(sizeof(thread_data_t) * threads);

    unsigned long long base = total / threads;
    unsigned long long rest = total % threads;

    for (int i = 0; i < threads; ++i) {
        td[i].points = base + (i < rest);
        td[i].inside = 0;
        td[i].seed   = (unsigned)time(NULL) ^ (i << 16);
        pthread_create(&tid[i], NULL, worker, &td[i]);
    }

    unsigned long long in_total = 0;
    for (int i = 0; i < threads; ++i) {
        pthread_join(tid[i], NULL);
        in_total += td[i].inside;
    }

    double pi = 4.0 * (double)in_total / (double)total;
    printf("π ≈ %.10f  (%llu puntos, %d hilos)\n", pi, total, threads);

    free(tid);
    free(td);
    return 0;
}
