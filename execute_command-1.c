#include "main.h"

/**
 * exec_command- executes a command
 * @av: array of arguments
 * @head: points to the start of the argument variables
 * Return: The exit value of the executed command, 
 * 	    error code on failure to execute
 */
int exec_command(char **av, char **head)
{
	pid_t c_pid;
	int return_value = 0, flag = 0;
	char *command;
	int status;

	command = av[0];
	/*checking whether the user has provided a path to a command*/
	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = find_command_in_path(command);
	}
	if ((access(command, F_OK) == -1) || !command)
	{
		if (errno == EACCES)
			return_value = print_error(av, 126);
		else
			return_value = (print_error(av, 127));
	}
	else
	{
		c_pid = fork();
		if (c_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (c_pid == 0)
		{
			execve(command, av, environ);
			if (errno == EACCES)
				return_value = (print_error(av, 126));
			free_env();
			free_av(av, head);
			_exit(return_value);
		}
		else
		{
			wait(&status);
			return_value = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return(return_value);
}

/**
 * free_av - Frees up memory
 * @av: A null-terminated double pointer containing commands/arguments.
 * @head: Points to the start of argument variables.
 */
void free_av(char **av, char **head)
{
	size_t i;

	for (i = 0; av[i] || av[i + 1]; i++)
		free(av[i]);
	free(head);
}