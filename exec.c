#include "main.h"

/**
 * execute_command - this executes the commands and environment variables
 * @cmd: command to execute
 */
void execute_command(char *cmd)
{
    int max_tokens = 64;
    char *actual_cmd;
    int i;
    char **argv = malloc(sizeof(char *) * max_tokens); // Dynamically allocate memory
    if (argv == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    parse_command(cmd, argv, max_tokens);
    actual_cmd = get_env(argv[0]);
    if (actual_cmd != NULL)
    {
        // Execute the command with execve()
        if (execve(actual_cmd, argv, NULL) == -1)
        {
            perror("Error: ");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("command not found: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // Free the dynamically allocated memory in argv
    for (i = 0; argv[i] != NULL; i++)
    {
        free(argv[i]);
    }
    free(argv);
}

int execute_commands(char *line)
{
    char *token;
    char *saveptr;
    int overall_exit_status = 0;      // Initialize to 0
    int last_command_exit_status = 0; // Initialize to 0

    for (token = strtok_r(line, ";", &saveptr); token != NULL; token = strtok_r(NULL, ";", &saveptr))
    {
        execute_command(token);
        last_command_exit_status = some_function_to_get_last_command_exit_status();
        if (overall_exit_status == 0)
        {
            overall_exit_status = last_command_exit_status;
        }
    }
    return overall_exit_status;
}

int some_function_to_get_last_command_exit_status(void)
{
    int exit_status;
    wait(&exit_status);
    return WEXITSTATUS(exit_status);
}

void ls_builtin(void)
{
    execute_command("ls -l");
}

void parse_command(char *command, char **argv, int max_tokens)
{
    char *token;
    int num_tokens = 0;
    // Split the command by spaces and store tokens in argv
    for (token = strtok(command, " "); token != NULL && num_tokens < max_tokens - 1; token = strtok(NULL, " "))
    {
        argv[num_tokens] = token;
        num_tokens++;
    }
    argv[num_tokens] = NULL;
}
