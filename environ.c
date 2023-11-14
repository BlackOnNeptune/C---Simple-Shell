#include "shell.h"

/**
 * my_env - prints the current environment variables
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * retrieve_env_var - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: name of the environment variable
 *
 * Return: the value of the variable
 */
char *retrieve_env_var(info_t *info, const char *name)
{
	list_t *ptr = info->env;
	char *p;

	while (ptr)
	{
		p = starts_with(ptr->str, name);
		if (p && *p)
			return (p);
		ptr = ptr->next;
	}
	return (NULL);
}

/**
 * set_env_var - Adds or modifies an existing environment variable
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error
 */
int set_env_var(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env_var - Removes an environment variable
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error
 */
int unset_env_var(info_t *info)
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
 * fill_env_list - populates environment linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int fill_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

