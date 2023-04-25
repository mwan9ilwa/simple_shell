#include "builtins.h"

/**
 * exec_exit - exit the shell
 *
 * Return: 0
 */
int exec_exit(void)
{
    return (0);
}

/**
 * exec_cd - change the current working directory
 * @args: the arguments to the cd command
 *
 * Return: 0 on success, -1 on failure
 */
int exec_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "cd: expected argument to \"cd\"\n");
		return (-1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("chdir");
			return (-1);
		}
	}

	return (0);
}
