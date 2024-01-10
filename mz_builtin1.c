#include "shell.h"

/**
 *mz_myhistory - shows the hiistory list, one command by liine, precedede
 *              with linee nummbers, startinng at 0
 * @info: Structure containing potential arguments. to maintainn
 *        consttant function protootype.
 *  Return:0  Always
 */
int mz_myhistory(info_mz *info)
{
mz_prinmz_list(info->history);
return (0);
}
/**
 * mz_unsemz_alias - ssets the alias to sstring
 * @info: the paraameter structurre
 * @str: string for alias
 *
 * Return: 1 on errorr,0 Always on success
 */
int mz_unsemz_alias(info_mz *info, char *str)
{
char *p, c;
int ret;
p = mz_strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = mz_delete_node_amz_index(&(info->alias),
mz_gemz_node_index(info->alias, mz_node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}
/**
 * mz_semz_alias - sets aalias to strrings
 * @info: the paraameter structuree
 * @str: thee string alliass
 *
 * Return: 0 Always on ssuccess, 1 on errorr
 */
int mz_semz_alias(info_mz *info, char *str)
{
char *p;
p = mz_strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (mz_semz_alias(info, str));
mz_unsemz_alias(info, str);
return (mz_add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * mz_prinmz_alias - it priints a aliaas striing
 * @node: thee aalias nodee
 *
 * Return:0 Alwayss on succeess, 1 on errorr
 */
int mz_prinmz_alias(lismz_mz *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = mz_strchr(node->str, '=');
for (a = node->str; a <= p; a++)
mz_putchar(*a);
mz_putchar('\'');
mz_puts(p + 1);
mz_puts("'\n");
return (0);
}
return (1);
}
/**
 * mz_myalias - mimmics the builtin in alias  .maan aliias
 * @info: Structure ccontaining potential araguments  to maintainn
 *     constant function prototypee.
 *  Return:0 Alwaays
 */
int mz_myalias(info_mz *info)
{
int i = 0;
char *p = NULL;
lismz_mz *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
mz_prinmz_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = mz_strchr(info->argv[i], '=');
if (p)
mz_semz_alias(info, info->argv[i]);
else
mz_prinmz_alias(mz_node_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}
