#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main()
{
	int idMem;
	int size;
	int *dato;

	size = 5;

	idMem = shmget(IPC_CREAT, size, 0660);

	if (fork() == 0)
	{
		printf("Hijo\n");
		dato = (int*)shmat(idMem, (char*) 0, 0);
		printf("Hijo %d\n", *dato);

		shmdt((char*)dato);
	}
	else
	{
		printf("Padre\n");
		dato = (int*)shmat(idMem, (char*) 0, 0);

		shmdt((char*)dato);

		wait(NULL);

		shmctl(idMem, IPC_RMID, 0);
	}

	return 0;
}

