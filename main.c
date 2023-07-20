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
    char *lineptr;
    size_t i = 0;
    /* declaring void variables */
    (void)ac;
    (void)argv;
    /*printing the prompt*/
    printf("%s", prompt);
    /* the getline built-in function grabs whatever is being typed */
    getline(&lineptr, &i, stdin);
    printf("%s\n", lineptr);
    /* frees the allocated memory */
    free(lineptr);
    return (0);
}
