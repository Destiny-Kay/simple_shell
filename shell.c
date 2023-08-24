#include "main.h"
#include <signal.h>
#include <unistd.h>

int counter = 0;
char *program_name = NULL;
/**
 * print_prompt- prints a new prompt to the STDOUT/ signal handler.
 * @a: integer that signals the the function to print a prompt
 * Return: void
 */
void print_prompt(int a)
{
	(void)a;
	signal(SIGINT, print_prompt);
	write(STDIN_FILENO, "\nhsh$ ", 6);
}


/**
 * is_interactive- checks whether a shell is in interactive mode or not
 * Return: 1 if interactive and 0 if not in interactive moded
 */
int is_interactive(void)
{
	int interactive = isatty(STDIN_FILENO);

	return (interactive);
}

/**
 * main- function entry point, main shell loop
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: return value of the executed command
 */
int main(int argc, char **argv)
{
	int return_val = 0, return_value;
	int *executable_return = &return_value;

	(void)argc;
	program_name = argv[0];/*Setting the programe name for handling errors*/
	counter = 1;
	environ = copyenviron();/*implement the copy env function*/
	*executable_return = 0;

	if (!environ)
		exit(-100);
	if (!is_interactive())
	{
		while (return_val != ENDOFFILE && return_val != -3)
			return_val = execute_cmd(executable_return);
		free_env();
		return (*executable_return);
	}

	while (1)
	{
		write(STDOUT_FILENO, "hsh$ ", 5);
		return_val = execute_cmd(executable_return);
		if (return_val == ENDOFFILE || return_val == -3)
		{
			if (return_val == ENDOFFILE)
				write(STDOUT_FILENO, "\n", 1);
			free_env();
			exit(*executable_return);
		}
	}

	free_env();
	return (*executable_return);
}
