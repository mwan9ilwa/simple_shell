#include "shell.h"

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

