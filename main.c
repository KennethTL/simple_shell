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
    ssize_t n_chars; /* Stores the number of characters in a line*/
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i, j;
    /* adding a loop*/
    while (1)
    {
        int pid;
        char **argv;
        char *cmd;
        char *actual_cmd;
        /*printing the prompt*/
        printf("%s", prompt);
        n_chars = getline(&line, &p, stdin);
        /* checks if the getline() fails or reach EOF, the getline built-in function grabs whatever is being typed */
        if (n_chars == -1)
        {
            printf("Exiting Shell...");
            return (-1);
        }
        /* we are trying to allocate space for the copy of whatver gets to be added in the line */
        line_copy = malloc(sizeof(char) * n_chars);
        if (line_copy == NULL)
        {
            perror("sh: memory allocation error");
            free(line); // Free line before exiting
            return (-1);
        }
        /* copy the line into the line variable */
        strcpy(line_copy, line);
        /* Splitting the string into array of tokens */
        token = strtok(line, delim);
        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;
        /* Allocating space for the array*/
        argv = malloc(sizeof(char *) * num_tokens);
        /* store each token in the array */
        token = strtok(line_copy, delim);
        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token) + 1); // Add +1 for the null terminator
            if (argv[i] == NULL)
            {
                perror("sh: memory allocation error");
                free(line_copy); // Free line_copy and argv[i] before exiting
                for (j = 0; j < i; j++)
                {
                    free(argv[j]);
                }
                free(argv);
                free(line);
                return (-1);
            }
            strcpy(argv[i], token);
            token = strtok(NULL, delim);
        }
        argv[i] = NULL;
        /* making sure fork isn't called if the cmd doesn't exist */
        cmd = argv[0];
        // Check if the user entered 'exit'
        if (strcmp(cmd, "exit") == 0)
        {
            printf("Exiting Shell...\n");
            break; // Exit the loop and terminate the shell
        }
        else if (strcmp(cmd, "env") == 0)
        {
            print_env();
        }
        else if (strcmp(cmd, "ls") == 0)
        {
            ls_builtin();
        }
        // Skip execution if the command is the shell program itself
        else if (strcmp(cmd, "./shell_0.3") == 0)
        {
            printf("command not found: %s\n", cmd);
            free(line_copy);
            for (i = 0; i < num_tokens; i++)
            {
                free(argv[i]);
            }
            free(argv);
            continue; // Go to the next iteration of the loop
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
                    execute_command(actual_cmd, argv);
                    perror("execve failed");
                    free(actual_cmd);
                    exit(EXIT_FAILURE);
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
        free(line_copy);
        for (i = 0; i < num_tokens; i++)
        {
            free(argv[i]);
        }
        free(argv);
    }
    /* frees the allocated memory */
    free(line);
    return (0);
}
