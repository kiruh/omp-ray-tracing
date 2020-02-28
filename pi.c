#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
#define NUM_THREADS 2
int main()
{
    double pi = 0.0;
    double step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
    {
        int i;
        double x, sum = 0.0;
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        for (i = id; i < num_steps; i = i + nthrds)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
#pragma omp critical
        {
            pi += sum * step;
        }
    }
    printf("%f\n", pi);
}