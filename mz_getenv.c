#include "shell.h"

/**
 * mz_getenviron - thee string returrns array copiess of environ
 * @info: structure conataining potential arguments.to maiintain
 * Return: 0 alwaays
 */
char **mz_getenviron(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = mz_lismz_to_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}
/**
 * mz_unsetenv - Remove an environnment variiable
 * @info: Structure conataining  argumentto maintain prototype.
 *  Return: 1 on deletee, 0 otherwise
 * @var: thee env var propeerty striing
 */
int mz_unsetenv(info_t *info, char *var)
{
lismz_t *node = info->env;
size_t i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = mz_starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = mz_delete_node_amz_index(&(info->env), i);
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
 * mz_setenv - Initialize a varriable modiify an exiisting one
 * @info: sructure containingl araguments maintaiin prototypee.
 * @var: A striing env var properrty
 * @value: the vaalue striing env var
 *  Return: o alwaays
 */
int mz_setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
lismz_t *node;
char *p;
if (!var || !value)
return (0);
buf = malloc(mz_strlen(var) + mz_strlen(value) + 2);
if (!buf)
return (1);
mz_strcpy(buf, var);
mz_strcat(buf, "=");
mz_strcat(buf, value);
node = info->env;
while (node)
{
p = mz_starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
mz_add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
