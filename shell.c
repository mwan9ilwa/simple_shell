#include shell.h

int main()
{
	char command[MAX_LINE];

	while (1)
	{
		char cwd[MAX_LINE];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("error");
			exit(1);
		}
		printf("#mzkk$ ");
		fflush(stdout);
		if (fgets(command, MAX_LINE, stdin) == NULL)
		{	printf("\n");
			exit(0);
		}
		if (command[strlen(command)-1] == '\n')
		{
			command[strlen(command)-1] = '\0';
		}
		char *args[MAX_LINE];
		int i = 0;
		char *token = strtok(command," ");
		while (token  != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		pid_t pid = fork();
		if (pid == 0)
		{	
			if execvp(args[0], args == -1)
			{
				perror("error");
				exit(1);
			}
			exit(0);
		}
		else if (pid > 0 )
		{
			wait(&status);
		}
		else 
		{
			printf("Failed to fork\n");
			exit(1);
		}
	}

	return 0;
}
