#include "shell.h"

/**
 * interactive_mode - returns true if the shell is in interactive mode
 * @info_shell: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive_mode(info_t *info_shell)
{
	return (isatty(STDIN_FILENO) && info_shell->readfd <= 2);
}

/**
 * is_delimiters - checks if a character is a delimiters
 * @ch: the character to check
 * @delimiters: the delimiters string
 *
 * Return: 1 if true, 0 if false
 */
int is_delimiters(char ch, char *delimiters)
{
	while (*delimiters)
	if (*delimiters++ == ch)
	return (1);
	return (0);
}

/**
 * is_alphabetic - checks for an alphabetic character
 * @ch: The character to be checked
 *
 * Return: 1 if 'ch' is alphabetic, 0 otherwise
 */
int is_alphabetic(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	return (1);
	else
	return (0);
}

/**
 * string_to_int - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: 0 if there are no numbers in the string,
 * the converted number otherwise
 */
int string_to_int(char *str)
{
	int current_index, multiplier_sign = 1, flag_state = 0, output;
	unsigned int res = 0;

	for (current_index = 0; str[current_index]
	!= '\0' && flag_state != 2; current_index++)
	{
	if (str[current_index] == '-')
	multiplier_sign *= -1;

	if (str[current_index] >= '0' && str[current_index] <= '9')
	{
	flag_state = 1;
	res *= 10;
	res += (str[current_index] - '0');
	}
	else if (flag_state == 1)
	flag_state = 2;
	}

	if (multiplier_sign == -1)
	output = -res;
	else
	output = res;

	return (output);
}

