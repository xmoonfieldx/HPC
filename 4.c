#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main()
{
	srand(time(0));
	int i, n=rand()%40;
	omp_set_num_threads(2);
	int a[100] = { 1,1 };
	printf("n:%d\n",n);
#pragma omp parallel
	{
		if (omp_get_thread_num() == 0)
		{
			printf("Using thread 0\n");
			printf("Computing series...\n\n");
			for (i = 2; i < n; i++)
				a[i] = a[i - 1] + a[i - 2];
		}
		if (omp_get_thread_num() == 1)
		{
			printf("Using thread 1\n");
			for (i = 0; i < n; i++)
				printf("%d ", a[i]);
		}
	}
}
