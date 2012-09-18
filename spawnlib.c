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

int spawn_tree(int n, int k)
{
	int i, j;

	i = 0;
	while (i < n / k)
	{
		for (j = 0; j < n; j++)
		{
			if (fork() == 0)
			{
				i = k * i + j;
				break;
			}
		}

		if (j > k)
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

int spawn_hypercube(int k)
{
	int i, j;

	i = 0;

	for (j = 0; j < k; j++)
		if (fork() == 0)
			i = (2 << j);
	return i;
}

int main()
{
	int value;

	value = spawn_tree(6, 2);

	printf("Value: %d\n", value);

	return 0;
}

