#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main()
{
	srand(time(0));
	int n = rand() % 30;
	printf("n: %d\n", n);
	int a[100], i;
	a[0] = 1, a[1]=1;
	omp_set_num_threads(2);
#pragma omp parallel
	{
		if (omp_get_thread_num() == 0)
		{
			for (i = 2; i < n; i++)
				a[i] = a[i - 2] + a[i - 1];
		}
		if(omp_get_thread_num()==1)
		{
			for (i = 0; i < n; i++)
				printf("%d ", a[i]);
		}
	}
/*#pragma omp parallel
	{
		if (omp_get_thread_num() == 0)
		{
			for (i = 2; i < n; i++)
			{
				a[i] = a[i - 1] + a[i - 2];
			}
		}
		if (omp_get_thread_num() == 1)
		{
			for (i = 0; i < n; i++)
				printf("%d ", a[i]);
		}
	}*/

}
