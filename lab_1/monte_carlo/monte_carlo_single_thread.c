#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "timer.h"


long n_trials;

int hits_in_circle = 0;


/// Function to get a random number between 0 and 1
double get_random_double()
{
    double random_num = (double)rand() / RAND_MAX;
    return random_num;
}

int main(int argc, char **argv)
{
    printf("Monte Carlo Pi\n");
    srand(time(NULL));

    n_trials = strtol(argv[1], NULL, 10);

    double start;
    GET_TIME(start);

    double x, y, d;
    for (int i = 0; i < n_trials; i++)
    {
        x = get_random_double();
        y = get_random_double();
        d = ((x * x) + (y * y));
        if (d < 1)
        {
            hits_in_circle++;
        }
    }

    double end;
    GET_TIME(end);

    printf("Time spent: %f\n", end - start);
    printf("Hits in circle: %ld\n", hits_in_circle);
    printf("Pi = %.20f\n", 4.0 * hits_in_circle / n_trials);

    return 0;
}