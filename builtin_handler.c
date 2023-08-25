#include "main.h"

/**
 * run_builtin_cmd - Finds a builtin function in a list of buitlin functions.
 * @command: command to search.
 * Return: Function to respective inbuilt function.
 */
int (*run_builtin_cmd(char *command))(char **av, char **head)
{
	int i;

	builtincomm_t builtinfunctions[] = {
		{ "exit", myexit },
		{ "cd", _cd },
		{ NULL, NULL }
	};

	for (i = 0; builtinfunctions[i].name; i++)
	{
		if (strcmp(builtinfunctions[i].name, command) == 0)
			break;
	}
	return (builtinfunctions[i].function);
}
