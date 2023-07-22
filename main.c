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
    char *lineptr = NULL; /* *lineptr_copy = NULL; */
    size_t i = 0;
    ssize_t nchars; /* This variables simply stores the number of characters in a line*/
    // const char *delim = " \n";
    // int num_tokens = 0;
    // char *token;
    // int i;
    /* declaring void variables */
    (void)ac;
    (void)argv;
    /* adding a loop*/
    while (1)
    {
        /*printing the prompt*/
        printf("%s", prompt);
        nchars = getline(&lineptr, &i, stdin);
        /* checks if the getline() fails or reach EOF,  the getline built-in function grabs whatever is being typed */
        if (nchars == -1)
        {
            printf("Exiting Shell...");
            return (-1);
        }
        /* we are trying to allocate space for the copy of whatver gets to be added in the lineptr */
        // lineptr_copy = malloc(sizeof(char) * nchars);
        printf("%s\n", lineptr);
    }
    /* frees the allocated memory */
    free(lineptr);
    return (0);
}
