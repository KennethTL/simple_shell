#include "main.h"
#define READ_SIZE 1024

/**
 * _getline - Custom getline function
 *
 * Return: Pointer to the line read or NULL if there's no more line to read or an error occurs
 */
char *_getline(void)
{
    static char buffer[READ_SIZE];
    static ssize_t buffer_size = 0;
    static ssize_t buffer_pos = 0;
    char *line = NULL;
    ssize_t n_chars = 0;
    ssize_t line_size = 0;
    while (1)
    {
        if (buffer_pos >= (ssize_t)buffer_size)
        {
            buffer_size = read(STDIN_FILENO, buffer, READ_SIZE);
            buffer_pos = 0;
            if (buffer_size <= 0)
            {
                return (NULL);
            }
        }

        if (line_size == 0 || (ssize_t)n_chars >= (ssize_t)line_size)
        {
            line_size += READ_SIZE;
            line = realloc(line, line_size);
            if (line == NULL)
            {
                return (NULL);
            }
        }
        while (buffer_pos < (ssize_t)buffer_size)
        {
            if (buffer[buffer_pos] == '\n')
            {
                line[n_chars] = '\0';
                buffer_pos++;
                return (line);
            }
            line[n_chars++] = buffer[buffer_pos++];
        }
    }
    // Will never reach here, but adding this to suppress warnings
    return (NULL);
}
