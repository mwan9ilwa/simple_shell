#include "shell.h"

int process_command(char *command)
{
	if (strcmp(command, "exit\n") == 0)
	{
		return (0);
	}
	else
	{
		if (access(command, F_OK) == 0 && access(command, X_OK) == 0)
		{
			return (exec_command(command));
		}
		else
		{
			fprintf(stderr, "Command not found: %s", command);
			return (-1);
		}
	}
}

