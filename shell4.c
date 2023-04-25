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
 * check_exit - check if the user entered the "exit" command
 * @command: the command entered by the user
 *
 * Return: 1 if the user entered "exit", 0 otherwise
 */
int check_exit(char *command)
{
	return strcmp(command, "exit\n") == 0;
}

/**
 * check_command - check if the command is valid and can be executed
 * @command: the command entered by the user
 *
 * Return: 1 if the command is valid and can be executed, 0 otherwise
 */
int check_command(char *command)
{
	return access(command, F_OK) == 0 && access(command, X_OK) == 0;
}

/**
 * run_interactive_shell - run the shell in interactive mode
 *
 * Return: 0 on success, non-zero on failure.
 */
int run_interactive_shell(void)
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

		if (check_exit(command))
		{
			break;
		}

		if (check_command(command))
		{
			exec_command(command);
		}
		else
		{
			fprintf(stderr, "Command not found: %s", command);
		}
	}

	return 0;
}

/**
 * run_scripted_shell - run the shell in scripted mode
 * @filename: the name of the file to read commands from
 *
 * Return: 0 on success, non-zero on failure.
 */
int run_scripted_shell(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	size_t len = 0;
	char *line = NULL;

	if (fp == NULL)
	{
		perror(filename);
		return EXIT_FAILURE;
	}

	while (getline(&line, &len, fp) != -1)
	{
		if (check_command(line))
		{
			exec_command(line);
		}
		else
		{
			fprintf(stderr, "Command not found: %s", line);
		}
	}

	fclose(fp);
	if (line)
		free(line);

	return 0;
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
	if (argc == 1)
	{
		return run_interactive_shell();
	}
	else if (argc == 2)
	{
		return run_scripted_shell(argv[1]);
	}
	else
	{
		fprintf(stderr, "Usage: %s [file]\n", argv[0]);
		return EXIT_FAILURE;
	}
}
