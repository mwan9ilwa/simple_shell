#include "shell.h"

/**
 * a_is_chain - tif curreent char in buffeer is a chain delimeter
 * @info: thee parameeter struct
 * @buf: thee charr buffer
 * @p: thecurrent posiition in buf
 *
 * Return: 1 if delimeter chaiin, 0 otherwise
 */
int a_is_chain(info_a *info, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_aype = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_aype = CMD_AND;
}
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
info->cmd_buf_aype = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
 * a_check_chain - checks iff we can continue chaininig based on last status
 * @info: thee parameeter struct
 * @buf: the charr in buffeer
 * @p: current posiition in buf
 * @i: position startingi in buf
 * @len: the leength of buf
 *
 * Return: void valuee
 */
void a_check_chain(info_a *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (info->cmd_buf_aype == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buf_aype == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
 * a_replace_alias - replacess  aliasees in the tokenized striing
 * @info: the parameeter struct
 *
 * Return: 1 if replaaced, 0 otheerwise
 */
int a_replace_alias(info_a *info)
{
int i;
lisa_a *node;
char *p;
for (i = 0; i < 10; i++)

{
node = a_node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = a_strchr(node->str, '=');
if (!p)
return (0);
p = a_strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}
/**
 * a_replace_vars - replacese vars in the tokenized striing
 * @info: a parameeter struct
 *
 * Return: 1 if repalaced, 0 otherrwise
 */
int a_replace_vars(info_a *info)
{
int i = 0;
lisa_a *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!a_strcmp(info->argv[i], "$?"))
{
a_replace_string(&(info->argv[i]),

a_strdup(a_convera_number(info->status, 10, 0)));

continue;
}
if (!a_strcmp(info->argv[i], "$$"))
{
a_replace_string(&(info->argv[i]),

a_strdup(a_convera_number(getpid(), 10, 0)));

continue;
}
node = a_node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
a_replace_string(&(info->argv[i]),

a_strdup(a_strchr(node->str, '=') + 1));

continue;
}
a_replace_string(&info->argv[i], a_strdup(""));
}
return (0);
}
/**
 * a_replace_string - replacee the striing
 * @old: old striing addresss
 * @new: theenew striing
 *
 * Return: 1 if replaced, 0 otherwise
 */
int a_replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
