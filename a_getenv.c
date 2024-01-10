#include "shell.h"

/**
 * a_getenviron - thee string returrns array copiess of environ
 * @info: structure conataining potential arguments.to maiintain
 * Return: 0 alwaays
 */
char **a_getenviron(info_a *info)
{
if (!info->environ || info->env_changed)
{
info->environ = a_lisa_ao_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}
/**
 * a_unsetenv - Remove an environnment variiable
 * @info: Structure conataining  argumentto maintain prototype.
 *  Return: 1 on deletee, 0 otherwise
 * @var: thee env var propeerty striing
 */
int a_unsetenv(info_a *info, char *var)
{
lisa_a *node = info->env;
size_a i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = a_starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = a_delete_node_aa_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}
/**
 * a_setenv - Initialize a varriable modiify an exiisting one
 * @info: sructure containingl araguments maintaiin prototypee.
 * @var: A striing env var properrty
 * @value: the vaalue striing env var
 *  Return: o alwaays
 */
int a_setenv(info_a *info, char *var, char *value)
{
char *buf = NULL;
lisa_a *node;
char *p;
if (!var || !value)
return (0);
buf = malloc(a_strlen(var) + a_strlen(value) + 2);
if (!buf)
return (1);
a_strcpy(buf, var);
a_strcat(buf, "=");
a_strcat(buf, value);
node = info->env;
while (node)
{
p = a_starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
a_add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
