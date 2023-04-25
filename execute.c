#include "execute.h"
#include "builtins.h"

/**
 * execute - execute a command
 * @args: the arguments to the command
 *
 * Return: 1 if the command was executed, 0 if it was not
 */
int execute(char **args)
{
	if (args[0] == NULL)
	{
		return (0);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		return (exec_exit());
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		return (exec_cd(args));
	}
	else
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("execvp");
				exit(errno);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(errno);
		}
		else
		{
			wait(NULL);
		}
	}

	return (1);
}

