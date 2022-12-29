#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#include <omp.h>
int main(int argc, char* argv[])
{
	int numtasks, rc, sz, prev, next, rank, count, inmsg;
	MPI_Status Stat;
	double start; 
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	sz = numtasks;
	start = omp_get_wtime();
	if (rank == 0) prev = sz - 1;
	else prev = rank - 1;
	if (rank == sz - 1) next = 0;
	else next = rank + 1;
	if (rank % 2 == 0 && rank < sz) {
		rc = MPI_Send(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
		rc = MPI_Recv(&inmsg, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &Stat);
	}
	else if (rank % 2 == 1 && rank < sz) {
		rc = MPI_Recv(&inmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &Stat);
		rc = MPI_Send(&rank, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) printf("Time taken by Blocking send/receive : %lf\n", omp_get_wtime() - start);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Request reqs[2];
	MPI_Status stats[2];
	start = omp_get_wtime();
	sz = numtasks;
	if (rank == sz - 1) next = 0;
	else next = rank + 1;
	if (rank == 0) prev = sz - 1;
	else prev = rank - 1;
	MPI_Irecv(&inmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &reqs[0]);
	MPI_Isend(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &reqs[1]);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) printf("Time taken by NonBlocking send/receive : %lf\n", omp_get_wtime() - start);
	MPI_Finalize();
	
	/*

	*/
}
