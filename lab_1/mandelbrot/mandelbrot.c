#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "timer.h"

double x_min = -2.0;
double x_max = 1.0;
double y_min = -1.0;
double y_max = 1.0;

FILE *file;
int thread_count;
unsigned long point_count;
pthread_mutex_t mutex;

bool point_is_in_mandelbrot_set(double real, double image)
{
    int tries = 4000;
    double local_real = 0;
    double local_image = 0;
    int i = 0;
    while (i < tries && local_real * local_real + local_image * local_image < 4)
    {
        double old_local_real = local_real;
        local_real = local_real * local_real - local_image * local_image + real;
        local_image = 2 * old_local_real * local_image + image;
        i++;
    }
    return i == tries;
}

void write_points_in_file(double *real, double *image, int count)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%f, %f\n", real[i], image[i]);
    }
    pthread_mutex_unlock(&mutex);
}

void *routine(void *rank)
{
    long my_rank = (long)rank;
    int point_per_thread = point_count / thread_count;
    int local_point_count = (int)floor(sqrt((double)point_per_thread));

    double x_range = x_max - x_min;
    double x_left = x_min + my_rank * x_range / thread_count;
    double x_right = x_left + x_range / thread_count;
    double x_step = (x_right - x_left) / local_point_count;

    double y_range = y_max - y_min;
    double y_step = y_range / local_point_count;

    double *real_result = malloc(point_per_thread * sizeof(double));
    double *image_result = malloc(point_per_thread * sizeof(double));

    int point_counter = 0;

    for (double real = x_left; real <= x_right; real += x_step)
    {
        for (double image = y_min; image <= y_max; image += y_step)
        {
            if (point_is_in_mandelbrot_set(real, image))
            {
                real_result[point_counter] = real;
                image_result[point_counter] = image;
                point_counter++;
            }
        }
    }
    write_points_in_file(real_result, image_result, point_counter);
}

int main(int argc, char const *argv[])
{
    thread_count = strtol(argv[1], NULL, 10);
    point_count = strtol(argv[2], NULL, 10);
    
    double start;
    GET_TIME(start);

    file = fopen("points.csv", "w+");
    fprintf(file, "real, image\n");

    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < thread_count; i++)
    {
        pthread_create(&threads[i], NULL, routine, (void *)i);
    }

    for (long i = 0; i < thread_count; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    double end;
    GET_TIME(end);

    printf("Time spent: %f\n", end - start);

    fclose(file);
    pthread_mutex_destroy(&mutex);
    free(threads);
    return 0;
}