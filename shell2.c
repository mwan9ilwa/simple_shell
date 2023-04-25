#include "shell.h"

/**
 * Main - main
 *
 * The program runs a shell interpretor
 *
 * @return 0 on success, non-zero on failure.
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

		if (strcmp(command, "/bin/ls\n") == 0)
		{
			pid_t pid = fork();

			if (pid == 0)
			{
			char *args[] = {"ls", NULL};

			execvp(args[0], args);

			exit(EXIT_FAILURE);
			}

			else if (pid < 0)
			{
				fprintf(stderr, "Failed to fork\n");
			}
			else
			{
				wait(NULL);
			}
		}
		else if (strcmp(command, "exit\n") == 0)
		{
			break;
		}
		else
		{
			fprintf(stderr, "Command unknown: %s", command);
		}
	}

	return (0);
}
