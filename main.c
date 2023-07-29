#include "main.h"
#include <unistd.h>

/**
 * main - Entry point for the shell
 * @argc: arg counter
 * @argv: arg to be evaluated
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	/* Load config files, if any */

	/* Run command loop */
	if (isatty(STDIN_FILENO) == 1)
	{
		sh_loop();
	} else
	{
		sh_loop_non_interactive();
	}

	/* Perform any shutdown/cleanup */
	return (EXIT_SUCCESS);
}
