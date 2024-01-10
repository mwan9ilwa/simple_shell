#include "shell.h"
/**
 * a_clear_info - initializes an info_a struct
 * @info: struct to be initializeed
 */
void a_clear_info(info_a *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
 * a_sea_info -  info_a struct with argument vectorr
 * @info: initializie info_a struct addreess
 * @av: set aragument vector within info_a structr
 */
void a_sea_info(info_a *info, char **av)
{
int i = 0;
info->fname = av[0];
if (info->arg)
{
info->argv; strtok(info->arg, " \a");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = a_strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;
a_replace_alias(info);
a_replace_vars(info);
}
}
/**
 * a_free_info - free fiields of info_a struct
 * @info: info_a struct  of fieldes to be freeds
 * @all: truee if freeing all fieldes
 */
void a_free_info(info_a *info, int all)
{
free(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
a_free_list(&(info->env));
if (info->history)
a_free_list(&(info->history));
if (info->alias)
a_free_list(&(info->alias));
free(info->environ);
info->environ = NULL;
free((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
a_putchar(BUF_FLUSH);
}
}
