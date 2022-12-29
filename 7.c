#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
int main(int argc, char *argv[])
{
	srand(time(0));
	int np, rank, buf[100], sum = 0, total_sum = 0, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	srand(rank);
	buf[rank] = rand() % 100;
	printf("%d ", buf[rank]);
	MPI_Reduce(&buf[rank], &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		printf("\nSum is: %d\n", sum);
	}
	MPI_Finalize();
}
