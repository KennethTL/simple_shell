#include "main.h"
#include <unistd.h>

/* List of builtin cmds with their corresponding functions */

/*
	*char *builtin_str[] = {
	* "cd",
	* "help",
	* "exit"
	* };
*/

int (*builtin_func[]) (char **) = {
	&sh_cd,
	&sh_help,
	&sh_exit
};

/**
 * sh_num_builtins - counts the number of builtin funcs
 * @void: no parameter
 * Return: number of functions
 */
int sh_num_builtins(void)
{
	char *builtin_str[] = {
		"cd",
		"help",
		"exit"
	};
	return (sizeof(builtin_str) / sizeof(char *));
}

/* Builtin function implementation */
/**
 * sh_cd - executes the chdir function
 * @args: command to be evaluated
 * Return: 0 on success, 1 on error
 */
int sh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sh: expected argument to \"cd\"\n");
	} else
	{
		if (chdir(args[1]) != 0)
		{
			perror("sh");
		}
	}

	return (1);
}

/**
 * sh_help - launches the shell man page
 * @args: arg to be evaluated
 * Return: 0 on success, 1 on error
 */
int sh_help(char **args)
{
	int i;
	char *builtin_str[] = {
		"cd",
		"help",
		"exit"
	};
	(void) args;

	printf("KT'S SH\n");
	printf("Type program names and arguments, then hit enter.\n");
	printf("The following are built in commands:\n");

	for (i = 0; i < sh_num_builtins(); i++)
	{
		printf("   %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");

	return (1);
}

/**
 * sh_exit - exits the shell
 * @args: arg to be evaluated
 * Return: 0 on success, 1 on error
 */
int sh_exit(char **args)
{
	(void) args;
	return (0);
}

/**
 * sh_execute - launches either a builtin command or system command
 * @args: command to be evaluated
 * Return: 0 on success, 1 on error
 */
int sh_execute(char **args)
{
	int i;
	char *builtin_str[] = {
		"cd",
		"help",
		"exit"
	};

	if (args[0] == NULL)
	{
		/* An empty command was retrieved */
		return (1);
	}

	for (i = 0; i < sh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}

	return (sh_launch(args));
}
