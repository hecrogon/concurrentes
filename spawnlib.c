#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int spawn_star(int num_child)
{
	int i;

	for (i = 0; i < num_child; i++)
	{
		if (fork() == 0)
			break;
		wait(NULL);
	}

	return i;
}

int spawn_list(int num_child)
{
	int i;

	for (i = 0; i < num_child; i++)
	{
		if (fork() != 0)
			break;
		wait(NULL);
	}

	return i;
}

int spawn_tree(int n)
{
	int i, j;

	i = 0;
	while (i < n / 2)
	{
		for (j = 0; j < n; j++)
		{
			if (fork() == 0)
			{
				i = 2 * i + j;
				break;
			}
		}

		if (j > 2)
			return i;
	}

	return i;
}

void spawn_matrix(int num_nodes, int *x, int *y)
{
	int i, j;

	for (i = 0; i < num_nodes; i++)
		if (fork() != 0)
			break;
	*x = i;

	for (j = 0; j < num_nodes; j++)
		if (fork() != 0)
			break;
	*y = 0;
}

int spawn_hypercube()
{

}

int main()
{
	int value;

	value = spawn_tree(6);

	printf("Value: %d\n", value);

	return 0;
}

