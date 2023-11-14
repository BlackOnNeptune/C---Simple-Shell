#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @information: parameter structure
 * @buffer: address of the buffer
 * @length: address of the length variable
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *information, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t length_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = 0;
		signal(SIGINT, interruptHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &length_p, stdin);
#else
		bytes_read = get_line(information, buffer, &length_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}
			information->linecount_flag = 1;
			remove_comments(*buffer);
			build_history(information, *buffer, information->histcount++);
			/* if (find_char(*buffer, ';')) is this a command chain? */
			{
				*length = bytes_read;
				information->cmd_buf = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * take_input - gets a line minus the newline
 * @information: parameter structure
 *
 * Return: bytes read
 */
ssize_t take_input(info_t *information)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buffer_p = &(information->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = buffer_input(information, &buffer, &len);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buffer position */
		p = buffer + i; /* get pointer for return */

		check_chain(information, buffer, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(information, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			information->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buffer_p = buffer; /* else not a chain, pass back buffer from _getline() */
	return (bytes_read); /* return length of buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @information: parameter structure
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *information, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line of input from STDIN
 * @information: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *information, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffer(information, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _find_char(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * interruptHandler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void interruptHandler(__attribute__((unused)) int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

