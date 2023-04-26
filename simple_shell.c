#include "shell.h"
#include "parser.h"
#include "execute.h"

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

