#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
	int np, rank, buf[100], sum = 0, total_sum = 0, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	for (i = 0; i < np; i++)
		buf[i] = rand() % 100;
	if (rank != 0)
		MPI_Send(&buf[rank], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		printf("Robot 0 picked %d mangoes.\n", buf[0]);
		total_sum += buf[0];
		for (i = 1; i < np; i++)
		{
			MPI_Recv(&sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Robot %d picked %d mangoes.\n", i, sum);
			total_sum += sum;
		}
		printf("\nTotal mangoes picked was %d\n", total_sum);
	}
	MPI_Finalize();
}
