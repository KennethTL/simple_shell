#include "main.h"

/**
 * _getline - Custom implementation of the getline function.
 * @lineptr: Pointer to the buffer storing the input string.
 * @n: Pointer to the size of the buffer.
 *
 * Return: Number of characters read (including the newline character),
 *         -1 on failure.
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	ssize_t n_chars = 0;
	ssize_t buffer_size = 1024;
	ssize_t buffer_pos = 0;
	int c;
	/* Check if lineptr is NULL */
	if (lineptr == NULL || n == NULL)
		return (-1);
	/* Allocate the initial buffer */
	*lineptr = malloc(buffer_size);
	if (*lineptr == NULL)
		return (-1);
	/* Read characters from input until newline or EOF is encountered */
	while ((c = getchar()) != EOF && c != '\n')
	{
		/* Check if buffer_pos exceeds buffer_size */
		if (buffer_pos >= buffer_size)
		{
			buffer_size += 1024;
			*lineptr = realloc(*lineptr, buffer_size);
			if (*lineptr == NULL)
				return (-1);
		}

		(*lineptr)[buffer_pos++] = c;
		n_chars++;
	}
	/* Add null terminator at the end of the line */
	if (buffer_pos >= buffer_size)
	{
		buffer_size += 1;
		*lineptr = realloc(*lineptr, buffer_size);
		if (*lineptr == NULL)
			return -1;
	}
	(*lineptr)[buffer_pos] = '\0';
	/* Update the size of the buffer */
	*n = buffer_size;
	/* Return the number of characters read */
	return n_chars;
}
