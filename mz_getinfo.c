#include "shell.h"
/**
 * mz_clear_info - initializes an info_mz struct
 * @info: struct to be initializeed
 */
void mz_clear_info(info_mz *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
 * mz_semz_info -  info_mz struct with argument vectorr
 * @info: initializie info_mz struct addreess
 * @av: set aragument vector within info_mz structr
 */
void mz_semz_info(info_mz *info, char **av)
{
int i = 0;
info->fname = av[0];
if (info->arg)
{
info->argv; strtok(info->arg, " \mz");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = mz_strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;
mz_replace_alias(info);
mz_replace_vars(info);
}
}
/**
 * mz_free_info - free fiields of info_mz struct
 * @info: info_mz struct  of fieldes to be freeds
 * @all: truee if freeing all fieldes
 */
void mz_free_info(info_mz *info, int all)
{
free(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
mz_free_list(&(info->env));
if (info->history)
mz_free_list(&(info->history));
if (info->alias)
mz_free_list(&(info->alias));
free(info->environ);
info->environ = NULL;
free((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
mz_putchar(BUF_FLUSH);
}
}
