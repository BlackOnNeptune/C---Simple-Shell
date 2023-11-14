#include "shell.h"

/**
 * retrieve_env - provides a copy of our environment variables
 * @information: Structure containing potential arguments, used to maintain
 *                constant function prototype.
 * Return: A string array copy of our environment variables
 */
char **retrieve_env(info_t *information)
{
	if (!information->env || information->env_modified)
	{
		information->env = list_to_strings(information->env);
		information->env_modified = 0;
	}

	return (information->environment);
}

/**
 * delete_env_var - Remove an environment variable
 * @information: Structure containing potential arguments, used to maintain
 *                constant function prototype.
 * @variable: the environment variable string
 * Return: 1 on deletion, 0 otherwise
 */
int delete_env_var(info_t *information, char *variable)
{
	list_t *node = information->env;
	size_t index = 0;
	char *pos;

	if (!node || !variable)
		return (0);

	while (node)
	{
		pos = starts_with(node->str, variable);
		if (pos && *pos == '=')
		{
			information->env_modified = delete_node_at_index(&(information->env),
					index);
			index = 0;
			node = information->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (information->env_modified);
}

/**
 * set_env_var - Initialize or modify an environment variable
 * @information: Structure containing potential arguments, used to maintain
 *                constant function prototype.
 * @variable: the environment variable property
 * @value: the environment variable value
 * Return: Always 0
 */
int set_env_var(info_t *information, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *pos;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = information->env;
	while (node)
	{
		pos = starts_with(node->str, variable);
		if (pos && *pos == '=')
		{
			free(node->str);
			node->str = buffer;
			information->env_modified = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(information->env), buffer, 0);
	free(buffer);
	information->env_modified = 1;
	return (NULL);
}

