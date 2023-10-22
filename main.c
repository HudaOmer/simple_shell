#include "main.h"

/**
 * main - the shell interpreter main entrance
 * @argc: the argument count
 * @argv: the argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv, char *envp[])
{
	data_t data[] = { DATA_INIT};
	(void)argc; (void)argv;
	while (1)
	{
		prompt(data);
		parse(data);
		execute(data);
	}

	return (0);

}
