#include "main.h"
/**
 * shellby_exit - Causes normal process termination
 *                for the shellby shell.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
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

/*int _cd(char **args)
{
    if (args[1] == NULL)
    {
        const char **home_dir = mygetenv("HOME");
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
} STILL WORKING ON IT*/