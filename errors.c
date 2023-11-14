#include "shell.h"

/**
 * wrt_stderr - prints a string to the standard error
 * @str: the string to be printed
 *
 * Return: null
 */
void wrt_stderr(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		wrt_stderr_char(str[index]);
		index++;
	}
}

/**
 * wrt_stderr_char - writes a character to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int wrt_stderr_char(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * wrt_fd_char - writes a character to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int wrt_fd_char(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * wrt_fd - prints a string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int wrt_fd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += write_fd_char(*str++, fd);
	}
	return (index);
}

