#include "main.h"

/**
 * main - Building a Shell that's interactive
 * @ac: arguments count
 * @argv: arguments
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **argv)
{
	char *prompt = "shell $ ", *token;
	char *line = NULL, *line_copy = NULL; /* stores command and shell args */
	size_t p = 0;
	ssize_t n_chars; /* Stores the number of characters in a line*/
	const char *delim = " \n";
	int num_tokens = 0, i, pid;
	(void)ac; /* declaring void variables */

	while (1) /* adding a loop*/
	{
		printf("%s", prompt); /*printing the prompt*/
		n_chars = getline(&line, &p, stdin);
		if (n_chars == -1) /*EOF checker*/
		{
			printf("Exiting Shell...");
			return (-1);
		}
		line_copy = malloc(sizeof(char) * n_chars);
		if (line_copy == NULL)
		{
			perror("sh: memory allocation error");
			return (-1);
		}
		strcpy(line_copy, line); /* cpy the line into the line var */
		token = strtok(line, delim); /* Split string -> array of tokens*/
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;
		argv = malloc(sizeof(char *) * num_tokens); /* Array mem allocation*/
		token = strtok(line_copy, delim); /* store each token in the array */
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		pid = fork(); /* process creation in order for the shell not to break*/
		if (pid == -1)
		{
			perror("fork failed");
			return (-1);
		}
		else if (pid == 0)
		{
			exec(argv);
			return (0);
		}
		else
			wait(NULL);
		printf("%s\n", line);
	}
	free(line); /* frees the allocated memory */
	free(line_copy);
	return (0);
}
