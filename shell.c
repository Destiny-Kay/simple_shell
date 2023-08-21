#include "main.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _myexit- An inbuilt exit function, exits the shell
 * @args: the arguments that contain the exit status of the shell
 * Return: integer representing the exit status of the shell.
 */
int _myexit(char **args) {
	if (args[1] != NULL)
	{
		int exit_status = atoi(args[1]);
		exit (exit_status);
	}
	exit(0);
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
 * execute_builtin_command- executes a builtin command
 * @tokens: the command and arguments to be executed
 * Return: returns the exit status of executed command
 *
 */
int execute_builtin_command(char **tokens)
{
	int i, return_value = -1;

	command_table builtin_list[] = {
		{"exit", _myexit},
		/*{"cd", _cd},
		{"env", _env},
		{NULL, NULL}*/
	};
	for (i = 0; builtin_list[i].command; i++)
	{
		if (strcmp(tokens[0], builtin_list[i].command) == 0)
		{
			return_value = builtin_list[i].function(tokens);
			break;
		}
	}
	return (return_value);
}
/**
 * execute_external_commands- executes external commands
 * @tokens: the tokens that contain the command and to be executed and its arguments
 * @shell_path - the path string to the shell
 * Return: 0 on succcess and -1 on failure
 *
*/
int execute_external_commands(char **tokens, char *shell_path)
{
	pid_t child_pid;
	int status;

	/*FIND COMMAND IN PATH: handle path*/
	child_pid = fork();
	if (child_pid == 0)
	{
		char *const *args = tokens;
		/*getting env*/char *const env[] = {NULL};

		if (execve(tokens[0], args, env) == -1)
		{
			printf("%s this is the path to the shell", shell_path);
			perror("shell_path");
			return (EXIT_FAILURE);
		}
		else if (child_pid < 0)
			perror("fork");
		else
			wait(&status);/*WAITING FOR CHILD PROCESS TO COMPLETE EXECUTION*/
	}
	return (0);
}
/**
 * hsh- the shell loop
 *
 * Return: exit code of executed commands
*/
int hsh(char **av)
{
	int nread, inbuilt_return_value = 0;
	char *line = NULL, **tokens;
	size_t len;
	char *shell_path = av[0];/*PATH TO SHELL*/

	while (1)
	{
		if (is_interactive())
			write(STDIN_FILENO, "$ ", 2);
		fflush(stdout);
		nread = getline(&line, &len, stdin);/*GETING USER INPUT*/
		if (nread == -1)
		{
			if (is_interactive())
				printf("\n");
			break;
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';/*replacing the newline character w*/
		tokens = tokenize_input(line, " ");
		/*HANDLING EMPTY INPUT*/
		if (tokens[0] == NULL /*|| tokens[0] == '#' */)
		{
			free(tokens);
			continue;
		}
		/*HANDLE INBUILT COMMANDS*/
		inbuilt_return_value = execute_builtin_command(tokens);
		if (inbuilt_return_value == -1)
			execute_external_commands(tokens, shell_path);/*EXECUTE COMMAND IN PATH IF IT DOES NOT EXIST IN INBUILT FUNCTIONS*/
	}
	if (line)
		free(line);
	return (0);
}

/**
 * main- function entry point
 * Return: the exit status of 
*/
int main(int ac, char **av)
{
	(void)ac;
	return (hsh(av));
}
