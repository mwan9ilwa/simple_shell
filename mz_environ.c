#include "shell.h"
/**
 * mz_myenv - priints the present enviroonment
 * @info: maintain araguments of the prototype.
 * Return:0  Always
 */
int mz_myenv(info_mz *info)
{
mz_prinmz_lismz_str(info->env);
return (0);
}
/**
 * mz_getenv - retrieve the value of an environmeent variable
 * @info: gives thee potential arguments used for prototypee
 * @name: env var name
 *
 * Return: return value
 */
char *mz_getenv(info_mz *info, const char *name)
{
lismz_mz *node = info->env;
char *p;
while (node)
{
p = mz_starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}
/**
 * mz_mysetenv - code a new environmeent variable,
 *             or change a exiisting onee
 * @info:Structure containing araguments to maintain protootype
 *  Return: 0 Always
 */
int mz_mysetenv(info_mz *info)
{
if (info->argc != 3)
{
mz_eputs("Incorrect number of arguements\n");
return (1);
}
if (mz_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
 * mz_myunsetenv -  environnment variable is remooved
 * @info: Structure containiing potential arguments to maintain
 *        prototypee
 * Return:0 Always
 */
int mz_myunsetenv(info_mz *info)
{
int i;
if (info->argc == 1)
{
mz_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
mz_unsetenv(info, info->argv[i]);
return (0);
}
/**
 * mz_populate_env_list - it popuulates env linkeed lists
 * @info: Structure conotaining potentiial araguments prototypee
 * Return: 0 Always
 */
int mz_populate_env_list(info_mz *info)
{
lismz_mz *node = NULL;
size_mz i;
for (i = 0; environ[i]; i++)
mz_add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
