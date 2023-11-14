#include "shell.h"

/**
 * initialize_infor - initializes info_t structure
 * @details: structure address
 */
void initialize_infor(info_t *details)
{
	details->arg = NULL;
	details->arguments = NULL;
	details->location = NULL;
	details->argument_count = 0;
}

/**
 * configure_infor - initializes info_t structure
 * @details: structure address
 * @vector: argument vector
 */
void configure_infor(info_t *details, char **vector)
{
	int index = 0;

	details->name = vector[0];
	if (details->arg)
	{
		details->arguments = strtow(details->arg, " \t");
		if (!details->arguments)
		{
			details->arguments = malloc(sizeof(char *) * 2);
			if (details->arguments)
			{
				details->arguments[0] = _strdup(details->arg);
				details->arguments[1] = NULL;
			}
		}
		for (index = 0; details->arguments && details->arguments[index]; index++)
			;
		details->argument_count = index;

		replace_data(details);
		replace_variables(details);
	}
}

/**
 * erase_infor - frees info_t structure fields
 * @details: structure address
 * @release: true if freeing all fields
 */
void erase_infor(info_t *details, int release)
{
	ffree(details->arguments);
	details->arguments = NULL;
	details->location = NULL;
	if (release)
	{
		if (!details->cmd_buf)
			free(details->arg);
		if (details->env)
			free_list(&(details->env));
		if (details->history)
			free_list(&(details->history));
		if (details->alias)
			free_list(&(details->alias));
		ffree(details->environ);
		details->environ = NULL;
		bfree((void **)details->cmd_buf);
		if (details->readfd > 2)
			close(details->readfd);
		_putchar(BUF_FLUSH);
	}
}

