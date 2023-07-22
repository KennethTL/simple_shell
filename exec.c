#include "main.h"
/**
 * exec: - this executes the commands and environment variables
 *
 * Return: argv
 */

void exec(char **argv)
{
    char *cmd = NULL;
    if (argv)
    {
        /* grab the command */
        cmd = argv[0];
        /* execute the command with the execve()*/
        if (execve(cmd, argv, NULL) == -1)
        {
            perror("Error: ");
        };
    }
}
