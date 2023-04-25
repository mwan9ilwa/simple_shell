#include <stdio.h>

int main(void)
{
	char command[80];

	while (1)
	{
		printf("mzkk$ ");
		fgets(command, sizeof(command), stdin);

		printf("%s", command);
	}

	return (0);
}
