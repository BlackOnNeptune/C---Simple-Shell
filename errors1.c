#include "shell.h"

/**
 * error_conv - converts a string to an integer
 * @string: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int error_conv(char *string)
{
	int index = 0;
	unsigned long int result = 0;

	if (*string == '+')
		string++;
	for (index = 0; string[index] != '\0'; index++)
	{
		if (string[index] >= '0' && string[index] <= '9')
		{
			result *= 10;
			result += (string[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_custom_err - prints a custom error message
 * @info_return: the parameter & return info struct
 * @err_string: string containing specified error type
 * Return: None
 */
void print_custom_err(info_t *info_return, char *err_string)
{
	_eputs(info_return->filename);
	_eputs(": ");
	print_decimal(info_return->line_counter, STDERR_FILENO);
	_eputs(": ");
	_eputs(info_return->argv[0]);
	_eputs(": ");
	_eputs(err_string);
}

/**
 * print_deci - prints a decimal (integer) number (base 10)
 * @input: the input
 * @file_descri: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_deci(int input, int file_descri)
{
	int (*custom_putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute, current;

	if (file_descri == STDERR_FILENO)
		custom_putchar = _eputchar;
	if (input < 0)
	{
		absolute = -input;
		custom_putchar('-');
		count++;
	}
	else
		absolute = input;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	custom_putchar('0' + current);
	count++;

	return (count);
}

/**
 * number_conv - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *number_conv(long int num, int base, int flags)
{
	static char *char_array;
	static char conversion_buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & UNSIGNED_CONVERT) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	char_array = flags & LOWERCASE_CONVERT ? "0123456789abcdef"
		: "0123456789ABCDEF";
	ptr = &conversion_buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = char_array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comment_remov - replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void comment_remov(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

