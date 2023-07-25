#include "main.h"

/**
 * main - Building a Shell that's interactive
 *
 * Return: 0 on success, 1 on error
 */

int main(void)
{
    char *prompt = "shell $ ";
    /* below, this stores whatever is being typed in the shell */
    char *line = NULL, *line_copy = NULL;
    size_t p = 0;
    ssize_t n_chars;     /* Stores the number of characters in a line */
    int max_tokens = 64; // Adjust this to your desired maximum number of tokens
    char **tokens;
    int num_tokens;
    char *token;
    int i, j;
    /* adding a loop */
    while (1)
    {
        int pid;
        char **argv;
        char *cmd;
        char *actual_cmd;
        /* Working with exits */
        /* int exit_status = 0; */
        /* printing the prompt */
        printf("%s", prompt);
        n_chars = _getline(&line, &p); // Use _getline() instead of getline()
        /* checks if the _getline() fails or reach EOF */
        if (n_chars == -1)
        {
            printf("Exiting Shell...");
            return (-1);
        }
        tokens = malloc(sizeof(char *) * max_tokens);
        if (tokens == NULL)
        {
            perror("sh: memory allocation error");
            free(line);
            return (-1);
        }
        num_tokens = get_tokens(line, tokens, max_tokens);
        /* we are trying to allocate space for the copy of whatever gets to be added in the line */
        line_copy = malloc(sizeof(char) * n_chars);
        if (line_copy == NULL)
        {
            perror("sh: memory allocation error");
            free(line); // Free line before exiting
            free(tokens);
            return (-1);
        }
        /* copy the line into the line variable */
        strcpy(line_copy, line);
        /* Splitting the string into an array of tokens */
        num_tokens = 0;
        token = line_copy;
        while (*token != '\0' && *token != '\n')
        {
            /* Skip leading spaces */
            while (*token == ' ')
                token++;
            if (*token == '\0' || *token == '\n')
                break;
            char *end_of_token = token;
            /* Find the end of the token */
            while (*end_of_token != ' ' && *end_of_token != '\0' && *end_of_token != '\n')
                end_of_token++;
            /* Allocate space for the token and copy it */
            size_t token_length = end_of_token - token;
            tokens[num_tokens] = malloc(token_length + 1); // Add +1 for the null terminator
            if (tokens[num_tokens] == NULL)
            {
                perror("sh: memory allocation error");
                free(line_copy); // Free line_copy and tokens before exiting
                for (i = 0; i < num_tokens; i++)
                {
                    free(tokens[i]);
                }
                free(tokens);
                free(line);
                return (-1);
            }
            strncpy(tokens[num_tokens], token, token_length);
            tokens[num_tokens][token_length] = '\0';
            num_tokens++;
            token = end_of_token;
        }
        tokens[num_tokens] = NULL;
        /* making sure fork isn't called if the cmd doesn't exist */
        cmd = tokens[0];
        // Check if the user entered 'exit'
        if (strcmp(tokens[0], "exit") == 0)
        {
            if (num_tokens > 1) /* Check if there is an argument for the 'exit' command */
            {
                int exit_status = atoi(tokens[1]); /* Convert the argument to an integer */
                printf("Exiting Shell with status %d...\n", exit_status);
                free_tokens(tokens);
                free(line);
                return exit_status; /* Return the exit status to main and terminate the shell */
            }
            else
            {
                printf("Exiting Shell...\n");
                free_tokens(tokens);
                free(line);
                return 0; /* Return 0 to main and terminate the shell */
            }
        }
        else if (strcmp(cmd, "env") == 0)
        {
            print_env();
        }
        else if (strcmp(cmd, "ls") == 0)
        {
            ls_builtin();
        }
        /* Skip execution if the command is the shell program itself */
        else if (strcmp(cmd, "./shell_0.3") == 0 || strcmp(cmd, "./shell_0.4.1") == 0)
        {
            printf("command not found: %s\n", cmd);
            free_tokens(tokens);
            continue; /* Go to the next iteration of the loop */
        }
        else
        {
            actual_cmd = get_env(cmd);
            if (actual_cmd != NULL)
            {
                /* need to create another process in order for the shell not to break*/
                pid = fork();
                if (pid == -1)
                {
                    perror("fork failed");
                    return -1;
                }
                else if (pid == 0)
                {
                    execute_command(actual_cmd, tokens);
                    perror("execve failed");
                    free(actual_cmd);
                    free_tokens(tokens);
                    free(line_copy);
                    free(line);
                    return 1;
                }
                else
                {
                    wait(NULL);
                }
                free(actual_cmd);
            }
            else
            {
                printf("command not found: %s \n", cmd);
            }
        }
        free_tokens(tokens);
        free(line_copy);
    }
    free(tokens);
    /* frees the allocated memory */
    free(line);
    return (0);
}

/* Function to free the tokens */
void free_tokens(char **tokens)
{
    int i;
    for (i = 0; tokens[i] != NULL; i++)
    {
        free(tokens[i]);
    }
    free(tokens);
}
