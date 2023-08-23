#include "main.h"

/**
 * mystrtok - returns tokens of a string.
 * @string: string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **mystrtok(char *string, char *delim)
{
	char **ptr;
	int index = 0, tokens, i, letters, j;

	tokens = count_tokens(string, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);
	for (i = 0; i < tokens; i++)
	{
		while (string[index] == *delim)
			index++;

		letters = delim_index(string + index, delim);

		ptr[i] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[i])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (j = 0; j < letters; j++)
		{
			ptr[i][j] = string[index];
			index++;
		}

		ptr[i][j] = '\0';
	}
	ptr[i] = NULL;
	ptr[i + 1] = NULL;

	return (ptr);
}

/**
 * delim_index - finds the delim index, thus 
 * specifies end of first token
 * @str: The string to be searched.
 * @delim: The delimiter character.
 * Return: delim index
 */
int delim_index(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length++;
		index++;
	}
	return (length);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += delim_index(str + index, delim);
		}
	}

	return (tokens);
}

