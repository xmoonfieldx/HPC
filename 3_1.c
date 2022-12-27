#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main()
{
	int num = 1000, i;
	double step = 1.0 / (double)num, pi = 0.0;
	omp_set_num_threads(num);
#pragma omp parallel for
	for (i = 0; i < num; i++)
	{
		double x = (i + 0.5) * step;
		double local_pi = 4.0*step/(1 + x * x);
#pragma omp atomic
		pi += local_pi;

	}
	printf("%lf", pi);
}
