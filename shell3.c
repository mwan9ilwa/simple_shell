#include "shell.h"

/**
 * exec_command - execute the command passed in as an argument
 * @command: the command to execute
 *
 * Return: 0 on success, -1 on failure
 */
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

/**
 * process_command - process a command entered by the user
 * @command: the command entered by the user
 *
 * Return: 0 if the command was processed successfully, -1 otherwise
 */
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

/**
 * main - the main function
 *
 * The program runs a shell interpreter
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[])
{
	char command[80];

	if (argc == 1)
	{
		while (1)
		{
			printf("mzkk$ ");

			if (fgets(command, sizeof(command), stdin) == NULL)
			{
				printf("\n");
				break;
			}

			if (process_command(command) == 0)
			{
				break;
			}
		}
	}
	else if (argc == 2)
	{
		FILE *fp = fopen(argv[1], "r");
		size_t len = 0;
		char *line = NULL;

		if (fp == NULL)
		{
			perror(argv[1]);
			return (EXIT_FAILURE);
		}

		while (getline(&line, &len, fp) != -1)
		{
			process_command(line);
		}

		fclose(fp);
		if (line)
			free(line);
	}
	else
	{
		fprintf(stderr, "Usage: %s [file]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
