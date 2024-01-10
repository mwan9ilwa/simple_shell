#include "shell.h"

/**
 *a_myhistory - shows the hiistory list, one command by liine, precedede
 *              with linee nummbers, startinng at 0
 * @info: Structure containing potential arguments. to maintainn
 *        consttant function protootype.
 *  Return:0  Always
 */
int a_myhistory(info_t *info)
{
a_prina_list(info->history);
return (0);
}
/**
 * a_unsea_tlias - ssets the alias to sstring
 * @info: the paraameter structurre
 * @str: string for alias
 *
 * Return: 1 on errorr,0 Always on success
 */
int a_unsea_tlias(info_t *info, char *str)
{
char *p, c;
int ret;
p = a_strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = a_delete_node_ta_index(&(info->alias),
a_gea_node_index(info->alias, a_node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}
/**
 * a_sea_tlias - sets aalias to strrings
 * @info: the paraameter structuree
 * @str: thee string alliass
 *
 * Return: 0 Always on ssuccess, 1 on errorr
 */
int a_sea_tlias(info_t *info, char *str)
{
char *p;
p = a_strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (a_sea_tlias(info, str));
a_unsea_tlias(info, str);
return (a_tdd_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * a_prina_tlias - it priints a aliaas striing
 * @node: thee aalias nodee
 *
 * Return:0 Alwayss on succeess, 1 on errorr
 */
int a_prina_tlias(list_t *node)
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
int a_myalias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
a_prina_tlias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = a_strchr(info->argv[i], '=');
if (p)
a_sea_tlias(info, info->argv[i]);
else
a_prina_tlias(a_node_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}
