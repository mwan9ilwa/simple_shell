#include <stdlib.h>
#include "shell.h"

extern char **environ;

/**
 * cexe - Executes a command using execve
 *
 * @argv: The arguments to the command
 *
 * @cmd: The command to read path
 *
 * @main_cmd: The actual command to read
 *
 * path_command - The path of the command
 *
 * execve - To execute command by filename
 *
 * perror - To print error if execvefails
 *
 * Return: void
 */
void cexe(char **argv)
{
  char *cmd = NULL;      /* Initialize variable for command */
  char *main_cmd = NULL; /* Initialize variable for path of command */
  pid_t child_pid;
  int status;

  if (argv) {  /* Check if arguments were provided */
    cmd = argv[0]; /* Get the command from the argument list */

    main_cmd = path_command(cmd); /* Get the path of the command */

    if (main_cmd == NULL) { /* Check if the command was found */
      fprintf(stderr, "%s: command not found\n", cmd);
      exit(EXIT_FAILURE);
    }

    child_pid = fork(); /* Create child process */

    if (child_pid == -1) { /* Check if fork failed */
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (child_pid == 0) { /* Child process */
      /* Execute command with arguments */
      if (execve(main_cmd, argv, environ) == -1) {
        fprintf(stderr, "%s: command not found\n", cmd);
        exit(EXIT_FAILURE);
      }
    } else { /* Parent process */
      /* Wait for child process to finish */
      if (wait(&status) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
      }

      /* Check if child process exited normally */
      if (WIFEXITED(status)) {
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("Child process terminated by signal %d\n", WTERMSIG(status));
      }
    }

    free(main_cmd); /* Free memory allocated for main_cmd */
  }
}
