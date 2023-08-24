#include "main.h"

/**
 * extract_command_av - Extracts commands from the standard input.
 * @line: store command buffer.
 * @execute_return: Return value executed command.
 * Return: NULL on fail and pointer to command on success
 *
 */
char *extract_command_av(char *line, int *execute_return)
{
	size_t n = 0;
	ssize_t nread;

	if (line)
		free(line);

	nread = _getline(&line, &n, STDIN_FILENO);/*make custom getline function*/
	if (nread == -1)
		return (NULL);
	if (nread == 1)
	{
		counter++;
		if (is_interactive())
			write(STDOUT_FILENO, "hsh$ ", 5);
		return (extract_command_av(line, execute_return));
	}

	line[nread - 1] = '\0';
	return (line);
}

/**
 * check_for_logical_ops - calls commands based on the logical
 * operators && and ||.
 * @av: Array of arguments.
 * @head: pointer to the head of argument variables.
 * @execute_return: Return value of executed command from the parent process.
 * Return: The value returned from last command execution.
 */
int check_for_logical_ops(char **av, char **head, int *execute_return)
{
	int return_val, i;

	if (!av[0])
		return (*execute_return);
	for (i = 0; av[i]; i++)
	{
		if (_strncmp(av[i], "||", 2) == 0)
		{
			free(av[i]);
			av[i] = NULL;
			return_val = run_command(av, head, execute_return);
			if (*execute_return != 0)
			{
				av = &av[++i];
				i = 0;
			}
			else
			{
				for (i++; av[i]; i++)
					free(av[i]);
				return (return_val);
			}
		}
		else if (strncmp(av[i], "&&", 2) == 0)
		{
			free(av[i]);
			av[i] = NULL;
			return_val = run_command(av, head, execute_return);
			if (*execute_return == 0)
			{
				av = &av[++i];
				i = 0;
			}
			else
			{
				for (i++; av[i]; i++)
					free(av[i]);
				return (return_val);
			}
		}
	}
	return_val = run_command(av, head, execute_return);
	return (return_val);
}

/**
 * run_command - Actual execution of a command.
 * @av: An array of arguments.
 * @head: Points to head node of av.
 * @execute_return: Return value from the parent process of executed command.
 * Return: The return value of the last executed command.
 */
int run_command(char **av, char **head, int *execute_return)
{
	int return_val, i;
	int (*builtin_func)(char **av, char **head);

	builtin_func = run_builtin_cmd(av[0]);

	if (builtin_func)
	{
		return_val = builtin_func(av + 1, head);
		if (return_val != -3)/*checking the exit condition*/
			*execute_return = return_val;
	}
	else
	{
		*execute_return = exec_command(av, head);
		return_val = *execute_return;
	}

	counter++;

	for (i = 0; av[i]; i++)
		free(av[i]);

	return (return_val);
}

/**
 * execute_cmd - Executes a command with its params.
 * @execute_return: Return value of the last executed command.
 * Return: On success - the return value of executed command.
 *          On EOF condition - returns -2
 */
int execute_cmd(int *execute_return)
{
	char **av, *line = NULL, **head;
	int return_val = 0, i;

	line = extract_command_av(line, execute_return);
	if (!line)
		return (ENDOFFILE);

	av = mystrtok(line, " ");
	free(line);
	if (!av)
		return (return_val);
	head = av;

	for (i = 0; av[i]; i++)
	{
		if (strncmp(av[i], ";", 1) == 0)
		{
			free(av[i]);
			av[i] = NULL;
			return_val = check_for_logical_ops(av, head, execute_return);
			av = &av[++i];
			i = 0;
		}
	}
	if (av)
		return_val = check_for_logical_ops(av, head, execute_return);

	free(head);
	return (return_val);
}
