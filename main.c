#include "main.h"

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
	sh_loop();

	/* Perform any shutdown/cleanup */
	return (EXIT_SUCCESS);
}
