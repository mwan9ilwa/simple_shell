#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char command[80];

	while (1)
	{
		printf("mzkk$ ");
		fgets(command, sizeof(command), stdin);

		if (strcmp(command, "/bin/ls\n") == 0)
		{
			char *args[] = {"ls", NULL};
			execvp(args[0], args);

		}
		else
		{
		printf("%s", command);
		}
	}

	return (0);
}
