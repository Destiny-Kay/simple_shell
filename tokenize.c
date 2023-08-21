#include "main.h"
#define MAX_TOKENS 100
/**
 * tokenize_input- tokenizes input string based on a delimiter
 * @input: the input string
 * @delim: the delimiter
 * Return: an array of tokens
 */

char **tokenize_input(const char *input, const char *delim)
{
	char *copy_input = strdup(input);
	char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
	int token_count = 0;

	if (copy_input != NULL && tokens != NULL)
	{
		char *token = strtok(copy_input, delim);
		
		while (token != NULL && token_count < MAX_TOKENS)
		{
			tokens[token_count] = strdup(token);
			token = strtok(NULL, delim);
			token_count++;
		}
		tokens[token_count] = NULL;
	}
	else
	{
		return (NULL);
	}
	return (tokens);
}
