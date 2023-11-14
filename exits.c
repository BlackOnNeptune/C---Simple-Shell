#include "shell.h"

/**
 * _copy_string - copies a string with a limit
 * @destination: the destination string to copy to
 * @source: the source string
 * @limit: the maximum number of characters to copy
 * Return: the concatenated string
 */
char *_copy_string(char *destination, char *source, int limit)
{
	int index, j;
	char *start = destination;

	index = 0;
	while (source[index] != '\0' && index < limit - 1)
	{
		destination[index] = source[index];
		index++;
	}
	if (index < limit)
	{
		j = index;
		while (j < limit)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (start);
}

/**
 * _concat_strings - concatenates two strings with a limit
 * @destination: the first string
 * @source: the second string
 * @limit: the maximum number of bytes to be used
 * Return: the concatenated string
 */
char *_concat_strings(char *destination, char *source, int limit)
{
	int i, j;
	char *start = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < limit)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < limit)
		destination[i] = '\0';
	return (start);
}

/**
 * _find_char - locates a character in a string
 * @string: the string to be parsed
 * @character: the character to search for
 * Return: (string) a pointer to the memory area 'string'
 */
char *_find_char(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (0);
}

