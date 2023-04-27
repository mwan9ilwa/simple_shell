#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: always 0
 */
int _myenv(info_t *info)
{
	list_t *node = info->env;

	while (node)
	{
		_puts(node->str);
		_puts("\n");
		node = node->next;
	}
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: environment variable name
 *
 * Return: the value of the environment variable
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	size_t len = _strlen(name);

	while (node)
	{
		if (_strncmp(node->str, name, len) == 0 && node->str[len] == '=')
			return (node->str + len + 1);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initialize a new environment variable or modify an existing one
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: always 0
 */
int _mysetenv(info_t *info)
{
	char *name, *value;

	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	name = _strdup(info->argv[1]);
	value = _strdup(info->argv[2]);
	if (_setenv(info, name, value))
	{
		free(name);
		free(value);
		return (0);
	}
	free(name);
	free(value);
	return (1);
}

/**
 * _myunsetenv - remove an environment variable
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * Populate_env_list - populates env linked list
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: always 0
 */
int Populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i, len;

	for (i = 0; environ[i]; i++)
	{
		len = _strlen(environ[i]);
		add_node_end(&node, environ[i], len);
	}
	info->env = node;
	return (0);
}
