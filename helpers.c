#include "main.h"
#include <sys/wait.h>

/**
 * sh_loop - initiates the shell prompt
 *
 * Return: 0 void
 */
void sh_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("($) ");
		line = sh_read_line();
		args = sh_split_line(line);
		status = sh_execute(args);

		free(line);
		free(args);
	} while (status);
}

/**
 * sh_read_line - reads a line from the standard input
 *
 * Return: characters from the command line
 */
char *sh_read_line(void)
{
	int bufsize = SH_RL_BUFSIZE;
	int position = 0;
	int c;
	char *buffer = malloc(sizeof(char) * bufsize);

	if (!buffer)
	{
		fprintf(stderr, "sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		/* Read a char */
		c = getchar();

		/* If EOF is reached, replace it with a null char and return */
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}

		buffer[position] = c;
		position++;

		/* If the buffer limit is exceeded, reallocate memory */
		if (position >= bufsize)
		{
			bufsize += SH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "sh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * sh_split_line - tokenizes the command from the shell
 * @line: read line from previous command
 * Return: tokenized characters
 */
char **sh_split_line(char *line)
{
	int bufsize = SH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, SH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += SH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));

			if (!tokens)
			{
				fprintf(stderr, "sh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, SH_TOK_DELIM);
	}

	tokens[position] = NULL;
	return (tokens);
}

/**
 * sh_launch - starts processes in the shell
 * @args: args to be evaluated
 * Return: 0 on success, 1 on error
 */
int sh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	(void) wpid;
	pid = fork();

	if (pid == 0)
	{
		/* Child process */
		if (execvp(args[0], args) == -1)
		{
			perror("sh");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		/* Error forking */
		perror("sh");
	} else
	{
		/* Parent process */
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
