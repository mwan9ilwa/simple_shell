#include "shell.h"

/**
 *a_myhistory - shows the hiistory list, one command by liine, precedede
 *              with linee nummbers, startinng at 0
 * @info: Structure containing potential arguments. to maintainn
 *        consttant function protootype.
 *  Return:0  Always
 */
int a_myhistory(info_a *info)
{
a_prina_list(info->history);
return (0);
}
/**
 * a_unsea_alias - ssets the alias to sstring
 * @info: the paraameter structurre
 * @str: string for alias
 *
 * Return: 1 on errorr,0 Always on success
 */
int a_unsea_alias(info_a *info, char *str)
{
char *p, c;
int ret;
p = a_strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = a_delete_node_aa_index(&(info->alias),
a_gea_node_index(info->alias, a_node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}
/**
 * a_sea_alias - sets aalias to strrings
 * @info: the paraameter structuree
 * @str: thee string alliass
 *
 * Return: 0 Always on ssuccess, 1 on errorr
 */
int a_sea_alias(info_a *info, char *str)
{
char *p;
p = a_strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (a_sea_alias(info, str));
a_unsea_alias(info, str);
return (a_add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * a_prina_alias - it priints a aliaas striing
 * @node: thee aalias nodee
 *
 * Return:0 Alwayss on succeess, 1 on errorr
 */
int a_prina_alias(lisa_a *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = a_strchr(node->str, '=');
for (a = node->str; a <= p; a++)
a_putchar(*a);
a_putchar('\'');
a_puts(p + 1);
a_puts("'\n");
return (0);
}
return (1);
}
/**
 * a_myalias - mimmics the builtin in alias  .maan aliias
 * @info: Structure ccontaining potential araguments  to maintainn
 *     constant function prototypee.
 *  Return:0 Alwaays
 */
int a_myalias(info_a *info)
{
int i = 0;
char *p = NULL;
lisa_a *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
a_prina_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = a_strchr(info->argv[i], '=');
if (p)
a_sea_alias(info, info->argv[i]);
else
a_prina_alias(a_node_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}
