#include "main.h"
/**
 * myexit- exits the shell
 * @args: argument variables
 * @front: pointer to args
 * Return: no args_-3,
 */
int myexit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (print_error(--args, 2));
		}
	}
	else
		return (-3);
	if (num > max - 1)
		return (print_error(--args, 2));
	args -= 1;
	free_av(args, front);
	free_env();
	exit(num);
}

