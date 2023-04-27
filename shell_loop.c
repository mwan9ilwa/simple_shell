#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;
    char *input;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (isatty(STDIN_FILENO))
            _puts("$ ");

        input = read_input(info);
        if (input == NULL)
            continue;

        parse_input(info, input);
        free(input);

        if (info->argc == 0)
            continue;

        builtin_ret = find_builtin(info);
        if (builtin_ret == -1)
            execute_cmd(info);
    }

    free_info(info);
    return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *          -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    }

    return (built_in_ret);
}

/**
 * execute_cmd - executes a command by forking a child process
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void execute_cmd(info_t *info)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork() failed");
        return;
    }
    else if (pid == 0)
    {
        execvp(info->argv[0], info->argv);
        perror("execvp() failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        info->status = WEXITSTATUS(status);
    }
}
