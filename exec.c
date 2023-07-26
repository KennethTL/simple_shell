#include "main.h"
/**
 * execute_command - this executes the commands and environment variables
 * @cmd: command to execute
 * @argv: arguments
 */
void execute_command(char *cmd, char **argv)
{
    char *actual_cmd = NULL;
    if (cmd)
    {
        /* generate the path to the command before running into execve */
        actual_cmd = get_env(cmd);
        if (actual_cmd != NULL)
        {
            /* execute the command with execve() */
            if (execve(actual_cmd, argv, NULL) == -1)
            {
                perror("Error: ");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("command not found: %s\n", cmd);
            exit(EXIT_FAILURE);
        }
    }
}
/**
 * ls_builtin - Execute the ls command (built-in)
 */
void ls_builtin(void)
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        return;
    }
    else if (pid == 0)
    {
        // Child process, execute ls command
        char *argv[] = {"ls", "-l", NULL};
        execvp("ls", argv);
        perror("execvp failed");
        exit(1);
    }
    else
    {
        // Parent process, wait for the child to finish
        wait(&status);
    }
}
