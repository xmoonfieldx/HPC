#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define n 1000
int main()
{
	int i;
	double x, local_pi, pi = 0.0, step = 1.0 / (double)n;
	double start = omp_get_wtime();
#pragma omp parallel for reduction(+:pi)
	for (i = 0; i < n; i++)
	{
		x = (i + 0.5)* step;
		local_pi = 4.0 * step / (1 + x * x);
		pi += local_pi;
	}
	printf("%lf %lf", pi, omp_get_wtime()-start);
}
