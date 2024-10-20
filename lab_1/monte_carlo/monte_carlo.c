#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include "timer.h"

int thread_count;

long n_trials;

int hits_in_circle = 0;

pthread_mutex_t mutex;

/// Function to get a random number between 0 and 1 
double get_random_double()
{
    double random_num = (double)rand() / RAND_MAX;
    return random_num;
}

void *routine(void *arg)
{
    int local_n = n_trials / thread_count;
    int local_hits_in_circle = 0;
    double x, y, d;
    for (int i = 0; i < local_n; i++)
    {
        x = get_random_double();
        y = get_random_double();
        d = ((x * x) + (y * y));
        if (d < 1)
        {
            local_hits_in_circle++;
        }
    }
    pthread_mutex_lock(&mutex);
    hits_in_circle += local_hits_in_circle;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
    printf("Monte Carlo Pi\n");
    srand(time(NULL));

    thread_count = strtol(argv[1], NULL, 10);
    n_trials = strtol(argv[2], NULL, 10);
    
    printf("Thread count: %d\n", thread_count);
    printf("Trials: %d\n", n_trials);

    double start;
    GET_TIME(start);
    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < thread_count; i++)
    {
        pthread_create(&threads[i], NULL, routine, NULL);
    }

    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }


    double end;
    GET_TIME(end);

    printf("Time spent: %f\n", end - start);
    printf("Hits in circle: %ld\n", hits_in_circle);
    printf("Pi = %.20f\n", 4.0 * hits_in_circle / n_trials);

    pthread_mutex_destroy(&mutex);
    free(threads);

    return 0;
}