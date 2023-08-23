#include "main.h"
#include <string.h>
/**
 * permission_denied_126-handles errors for permission denied
 * @av: array of arguments
 * Return: An error message
 */
char *permission_denied_126(char **av)
{
	int length;
	char *error;
	char *counterstring = integer_tostring(counter);

	if (!counterstring)
		return (NULL);

	length = strlen(program_name) + strlen(av[0]) + strlen(counterstring) + 24;
	error =  malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(counterstring);
		return (NULL);
	}
	strcpy(error, program_name);
	strcat(error, ": ");
	strcat(error, counterstring);
	strcat(error, ": ");
	strcat(error, av[0]);
	strcat(error, ": Permission denied\n");

	free(counterstring);
	return (error);
}

/**
 * command_not_found_127-handles errors for command not found
 * @av: array of arguments
 * Return: An error message
 */
char *command_not_found_127(char **av)
{
	int length;
	char *error;
	char *counterstring = integer_tostring(counter);

	if (!counterstring)
		return (NULL);

	length = strlen(program_name) + strlen(av[0]) + strlen(counterstring) + 16;
	error =  malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(counterstring);
		return (NULL);
	}
	strcpy(error, program_name);
	strcat(error, ": ");
	strcat(error, counterstring);
	strcat(error, ": ");
	strcat(error, av[0]);
	strcat(error, ": not found\n");

	free(counterstring);
	return (error);
}
