#include "main.h"
/**
 * exec - this executes the commands and environment variables
 * @argv: arguments
 * Return: argv
 */

void exec(char **argv)
{
    char *cmd = NULL, *actual_cmd = NULL;

    if (argv)
    {
        /* grab the command */
        cmd = argv[0];
        /* generate the path to the command before running into execve */
        actual_cmd = get_env(cmd);
        /* execute the command with the execve()*/
        if (execve(actual_cmd, argv, NULL) == -1)
        {
            perror("Error: ");
        };
    }
}
