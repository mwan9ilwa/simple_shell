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
			perror("./shell");
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
	command[strcspn(command, "\n")] = '\0';
	char *program = strtok(command, " ");
	char *args[80];

	args[0] = program;
	int i = 1;

	while ((args[i] = strtok(NULL, " ")) != NULL)
	{
		i++;
	}
	args[i] = NULL;

	if (strcmp(program, "/bin/ls") == 0)
	{
		return (execvp(args[0], args));
	}
	else if (strcmp(program, "exit") == 0)
	{
		return (0);
	}
	else
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			execvp(args[0], args);
			perror("./shell");
			exit(EXIT_FAILURE);
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
	}
	return (1);
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
	if (argc > 1)

	{
		for (int i = 1; i < argc; i++)
		{
			if (process_command(argv[i]) ==0)
			{
				break;
			}
		}
	}
	else
	{
		char command[80];

		while (1)
		{
			printf("#cisfun$ ");

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
	
	return (0);
}
