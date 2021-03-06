/*
* Con la función MPI_Sendrecv no se generan deadlocks
* Con el orden MPI_Send y MPI_Recv se generan aleatoriamente deadlocks,
* pero no siempre como en el ejercicio 41.c
*/

#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int size, rank, dest, source, count, tag=1;
	char inmsg, outmsg='x';
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
	  dest = 1;
	  source = 1;
		MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, tag, &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
	}else if (rank == 1) {
	  dest = 0;
	  source = 0;
    MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, tag, &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
	 }

	MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n",
		   rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	MPI_Finalize();
}
