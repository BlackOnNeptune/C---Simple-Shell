#include "shell.h"

/**
 * shell_exit - exits the shell
 * @shell_info: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if shell_info->argv[0] != "exit"
 */
int shell_exit(info_t *shell_info)
{
	int;

	if (shell_info->argv[1]) /* If exit_check there is an exit argument */
	{
	exit_check = _erratoi(shell_info->argv[1]);
	if (exit_check == -1)
	{
	shell_info->status = 2;
	print_error(shell_info, "Illegal number: ");
	_eputs(shell_info->argv[1]);
	_eputchar('\n');
	return (1);
	}
	shell_info->err_num = _erratoi(shell_info->argv[1]);
	return (-2);
	}
	shell_info->err_num = -1;
	return (-2);
}

/**
 * directory_change - changes the current directory of the process
 * @shell_info: Structure containing potential arguments.
 * Return: Always 0
 */
int directory_change(info_t *shell_info)
{
	char *currentDirectory, *targetDirectory, buffer[1024];
	int chdir_ret;

	currentDirectory = getcwd(buffer, 1024);
	if (!currentDirectory)
	_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shell_info->argv[1])
	{
	targetDirectory = _getenv(shell_info, "HOME=");
	if (!targetDirectory)
	chdir_ret = /* TODO: what should this be? */
	resultChdir((targetDirectory = _getenv(shell_info, "PWD="))
	? targetDirectory : "/");
	else
	chdir_ret = resultChdir(targetDirectory);
	}
	else if (_strcmp(shell_info->argv[1], "-") == 0)
	{
	if (!_getenv(shell_info, "OLDPWD="))
	{
	_puts(currentDirectory);
	_putchar('\n');
	return (1);
	}
	_puts(_getenv(shell_info, "OLDPWD=")), _putchar('\n');
	chdir_ret = /* TODO: what should this be? */
	resultChdir((targetDirectory = _getenv(shell_info, "OLDPWD="))
	? targetDirectory : "/");
	}
	else
	chdir_ret = resultChdir(shell_info->argv[1]);
	if (chdir_ret == -1)
	{
	print_error(shell_info, "can't cd to ");
	_eputs(shell_info->argv[1]), _eputchar('\n');
	}
	else
	{
	_setenv(shell_info, "OLDPWD", _getenv(shell_info, "PWD="));
	_setenv(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - displays help information
 * @shell_info: Structure containing potential arguments.
 * Return: Always 0
 */
int display_help(info_t *shell_info)
{
	char **arg;

	arg = shell_info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
	_puts(*arg); /* temporary att_unused workaround */
	return (0);
}
