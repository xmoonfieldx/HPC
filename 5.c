#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main()
{
	srand(time(0));
	int n = rand() % 100, i;
	double a[100], max=0.0;
	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 10 + (rand() % 100) * 0.01;
		printf("%.2lf ", a[i]);
	}
	printf("\n");
	omp_get_num_threads();
#pragma omp parallel
	{
		printf("%d: ", omp_get_thread_num());
#pragma omp parallel for
		for (i = 0; i < n; i++)
		{
#pragma omp critical
			if (a[i] > max)
				max = a[i];
		}
	}
	printf("\n%.2lf", max);

}
