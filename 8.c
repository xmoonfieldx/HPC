#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define SIZE 16
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
int main(int argc, char* argv[])
{
	int tag = 1, i, outbuf, source, rank, numtasks, dest,
		inbuf[4] = { MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL , MPI_PROC_NULL },
		nbrs[4], dims[2]={4,4}, periods[2] = {0,0}, reorder = 0, coords[2];
	MPI_Comm cartcomm;
	MPI_Status stats[8];
	MPI_Request reqs[8];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	if (numtasks == SIZE)
	{
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm, &rank);
		MPI_Cart_coords(cartcomm, rank, 2, coords);
		MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
		MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);
		printf("Rank: %d Coordinates %d %d Neighbors(u,d,l,r)= %d %d %d %d \n", rank, coords[0], coords[1], nbrs[UP], nbrs[DOWN], nbrs[LEFT], nbrs[RIGHT]);
		outbuf = rank;
		for (i = 0; i < 4; i++)
		{
			source = nbrs[i];
			dest = nbrs[i];
			MPI_Isend(&outbuf,1,MPI_INT,dest,tag,MPI_COMM_WORLD,&reqs[i]);
			MPI_Irecv(&inbuf[i], 1, MPI_INT, source, tag, MPI_COMM_WORLD, &reqs[i + 4]);

		}
		MPI_Waitall(8, reqs, stats);
		printf("Rank: %d inbuf(u,d,l,r)= %d %d %d %d\n", rank, nbrs[UP], nbrs[DOWN], nbrs[LEFT], nbrs[RIGHT]);

	}
	else
		printf("Terminating. \n");
	MPI_Finalize();
}
