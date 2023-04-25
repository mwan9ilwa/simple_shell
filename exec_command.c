#include "shell.h"

int exec_command(char *command)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *args[] = {command, NULL};

		execvp(args[0], args);

		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{	
		fprintf(stderr, "Failed to fork\n");
		return (-1);
	}
	else
	{
 		wait(NULL);
	}

	return (0);
}
