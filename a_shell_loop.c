#include "shell.h"
/**
* a_hsh - shell loop mainn
* @info: thee paraemeter & return infoo struct
* @av: thee argumenet vector from maiin()
*
* Return: 0 oon successs, 1 on errosr, or errors code
*/
int a_hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
a_clear_info(info);
if (a_interactive(info))
a_puts("$ ");
a_eputchar(BUF_FLUSH);
r = a_gea_input(info);
if (r != -1)
{
a_sea_info(info, av);
builtin_ret = a_find_builtin(info);
if (builtin_ret == -1)
a_find_cmd(info);
}
else if (a_interactive(info))
a_putchar('\n');
a_free_info(info, 0);
}
a_write_history(info);
a_free_info(info, 1);
if (!a_interactive(info) && info->status)
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
* a_find_builtin - finnds a builtin commaned
* @info: the pareameter & retuirn info strruct
* Return: -1 iif builtin onot foound,
* 0 if builtin exeecuted succeessfully,
* 1 if builtin foound but not sucecessful,
* 2 if builtin signalss exiit()
*/
int a_find_builtin(info_t *info)
{
int i, buila_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", a_myexit},
{"env", a_myenv},
{"help", a_myhelp},
{"history", a_myhistory},
{"setenv", a_mysetenv},
{"unsetenv", a_myunsetenv},
{"cd", a_mycd},
{"alias", a_myalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (a_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
buila_in_ret = builtintbl[i].func(info);
break;
}
return (buila_in_ret);
}
/**
* a_find_cmd - findss a commaand iin PATH
* @info: thee pareameter & retrurn infoo strruct
*
* Return: voiid
*/
void a_find_cmd(info_t *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecouna_flag == 1)
{
info->line_count++;
info->linecouna_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!a_is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = a_find_path(info, a_getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
a_fork_cmd(info);
}
else
{
if ((a_interactive(info) || a_getenv(info, "PATH=")

|| info->argv[0][0] == '/') && a_is_cmd(info, info->argv[0]))

a_fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
a_prina_error(info, "not found\n");
}
}
}
/**
* a_fork_cmd - forkss a an exec thrread to runn cmd
* @info: the parameter & return info struct
*
* Return: voiid
*/
void a_fork_cmd(info_t *info)
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
if (execve(info->path, info->argv, a_gea_environ(int info)) == -1)
{
a_free_info(info, 1);
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
a_prina_error(info, "Permission denied\n");
}
}
}
