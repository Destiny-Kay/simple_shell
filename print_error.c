#include "main.h"

/**
 * print_error- prints an error to the sterr
 * av: argument array
 * @av: argument variables
 *@err_val: the error value
 *Return:error value
 *
 */
int print_error(char **av, int err_val)
{
	char *err;

	switch (err_val)
	{
		case 126:
			err = permission_denied_126(av);
			break;
		case 127:
			err = command_not_found_127(av);
	}
	write(STDERR_FILENO, err, strlen(err));
	if (err)
		free(err);
	return (err_val);
}
