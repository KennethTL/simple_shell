#include "main.h"

/**
 * main - Building a Shell that's interactive
 * @ac:
 * @argv:
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **argv)
{
    char *prompt = "shell $ ";
    /* below, this stores whatever is being typed in the shell */
    char *line = NULL, *line_copy = NULL;
    size_t p = 0;
    ssize_t n_chars; /* This variables simply stores the number of characters in a line*/
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;
    /* declaring void variables */
    (void)ac;
    /* adding a loop*/
    while (1)
    {
        /*printing the prompt*/
        printf("%s", prompt);
        n_chars = getline(&line, &p, stdin);
        /* checks if the getline() fails or reach EOF,  the getline built-in function grabs whatever is being typed */
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
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);
            token = strtok(NULL, delim);
        }
        argv[i] = NULL;
        exec(argv);
        printf("%s\n", line);
    }
    /* frees the allocated memory */
    free(line);
    free(line_copy);
    return (0);
}
