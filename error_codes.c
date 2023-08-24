#include "main.h"
#include <string.h>


/**
 * generate_error_message - generates an error message based on the given parameters.
 * @av: array of arguments
 * @format: format string for the error message
 * @extra: extra information to include in the error message
 * Return: An error message
 */
char *generate_error_message(char **av, const char *format, const char *extra)
{
	int length;
	char *error;
	char *counterstring = integer_tostring(counter);

	if (!counterstring)
		return NULL;

	length = strlen(program_name) + strlen(av[0]) + strlen(counterstring) + strlen(format) + strlen(extra) + 1;
	error = malloc(sizeof(char) * length);
	if (!error)
	{
		free(counterstring);
		return NULL;
	}

	sprintf(error, format, program_name, counterstring, av[0], extra);

	free(counterstring);
	return error;
}

/**
 * permission_denied_126 - handles errors for permission denied
 * @av: array of arguments
 * Return: An error message
 */
char *permission_denied_126(char **av)
{
	return generate_error_message(av, "%s: %s: %s: Permission denied\n", "");
}

/**
 * command_not_found_127 - handles errors for command not found
 * @av: array of arguments
 * Return: An error message
 */
char *command_not_found_127(char **av)
{
	return generate_error_message(av, "%s: %s: %s: %s not found\n", "not found");
}
