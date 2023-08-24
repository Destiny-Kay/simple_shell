#include "main.h"
#include <stdio.h>

/**
 * _cd- builtin implementation of the cd function
 * @args: Argument variables
 * @head: head pointer to argument variables
 * Return: cd_return
*/
int _cd(char **args, char **head)
{
    (void)head;
	if (args[1] == NULL)
	{
		const char *home_dir = getenv("HOME");

		if (home_dir != NULL)
		{
			if (chdir(home_dir) != 0)
			{
				perror("cd");
				return (1);
			}
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (0);
		}
	}
	return (0);
}
