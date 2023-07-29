#include "main.h"

/**
 * print_env - Prints the current environment variables
 *
 * Returns: Always 0
 */

void print_env(void)
{
	int i;
	/* Accessing the environment variables */
	/*extern char **environ; -- declared in main.h */
	/* loop over the environment varibales to loop over them */
	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
