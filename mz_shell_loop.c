#include "shell.h"
/**
* mz_hsh - shell loop mainn
* @info: thee paraemeter & return infoo struct
* @av: thee argumenet vector from maiin()
*
* Return: 0 oon successs, 1 on errosr, or errors code
*/
int mz_hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
mz_clear_info(info);
if (mz_interactive(info))
mz_puts("$ ");
mz_eputchar(BUF_FLUSH);
r = mz_gemz_input(info);
if (r != -1)
{
mz_semz_info(info, av);
builtin_ret = mz_find_builtin(info);
if (builtin_ret == -1)
mz_find_cmd(info);
}
else if (mz_interactive(info))
mz_putchar('\n');
mz_free_info(info, 0);
}
mz_write_history(info);
mz_free_info(info, 1);
if (!mz_interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
/**
* mz_find_builtin - finnds a builtin commaned
* @info: the pareameter & retuirn info strruct
* Return: -1 iif builtin onot foound,
* 0 if builtin exeecuted succeessfully,
* 1 if builtin foound but not sucecessful,
* 2 if builtin signalss exiit()
*/
int mz_find_builtin(info_t *info)
{
int i, builmz_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", mz_myexit},
{"env", mz_myenv},
{"help", mz_myhelp},
{"history", mz_myhistory},
{"setenv", mz_mysetenv},
{"unsetenv", mz_myunsetenv},
{"cd", mz_mycd},
{"alias", mz_myalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (mz_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
builmz_in_ret = builtintbl[i].func(info);
break;
}
return (builmz_in_ret);
}
/**
* mz_find_cmd - findss a commaand iin PATH
* @info: thee pareameter & retrurn infoo strruct
*
* Return: voiid
*/
void mz_find_cmd(info_t *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecounmz_flag == 1)
{
info->line_count++;
info->linecounmz_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!mz_is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = mz_find_path(info, mz_getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
mz_fork_cmd(info);
}
else
{
if ((mz_interactive(info) || mz_getenv(info, "PATH=")

|| info->argv[0][0] == '/') && mz_is_cmd(info, info->argv[0]))

mz_fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
mz_prinmz_error(info, "not found\n");
}
}
}
/**
* mz_fork_cmd - forkss a an exec thrread to runn cmd
* @info: the parameter & return info struct
*
* Return: voiid
*/
void mz_fork_cmd(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, mz_gemz_environ(int info)) == -1)
{
mz_free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}

/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
mz_prinmz_error(info, "Permission denied\n");
}
}
}
