#include "shell.h"

/**
 * exec_ls - execute the ls command
 *
 * Return: 0 on success, -1 on failure
 */
int exec_ls(void)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *args[] = {"ls", NULL};

		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
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
	if (strcmp(command, "/bin/ls\n") == 0)
	{
		return (exec_ls());
	}
	else if (strcmp(command, "exit\n") == 0)
	{
		return (0);
	}
	else
	{
		char *program = strtok(command, " \n");
		char *args[] = {program, NULL};

		execvp(args[0], args);

		perror("execvp");
		return (-1);
	}
}

/**
 * main - the main function
 *
 * The program runs a shell interpreter
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(void)
{
	char command[80];

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

	return (0);
}
