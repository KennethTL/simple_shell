#include "main.h"

/**
 * get_tokens - Tokenizes the input line using spaces and newline as delimiters.
 * @line: The input line to be tokenized.
 * @tokens: Pointer to the array that will store the tokens.
 * @max_tokens: Maximum number of tokens that can be stored in the array.
 *
 * Return: Number of tokens found.
 */
int get_tokens(char *line, char *tokens[], int max_tokens)
{
	int num_tokens = 0;
	char *token_start = line;
	char *current = line;
	while (*current != '\0')
	{
		if (*current == ' ' || *current == '\n')
		{
			*current = '\0'; // Null-terminate the token
			tokens[num_tokens] = token_start;
			num_tokens++;
			if (num_tokens >= max_tokens)
				break;
			// Move to the next non-space character
			while (*current == ' ' || *current == '\n')
				current++;

			token_start = current;
		}
		else
		{
			current++;
		}
	}
	/* Add the last token if there's room in the array */
	if (num_tokens < max_tokens)
	{
		tokens[num_tokens] = token_start;
		num_tokens++;
	}
	return (num_tokens);
}
