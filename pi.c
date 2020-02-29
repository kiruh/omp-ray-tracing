#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
#define NUM_THREADS 2
void main()
{
    omp_set_num_threads(NUM_THREADS);
    int i;
    double sum = 0.0;
    double step = 1.0 / (double)num_steps;
#pragma omp parallel
    {
        double x;
#pragma omp for reduction(+ \
                          : sum)
        for (i = 0; i < num_steps; i++)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    }
    double pi = sum * step;
    printf("%f\n", pi);
}