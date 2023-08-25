#include "main.h"

/**
 * _env-prints the current working environment
 * @env:array of environmental variables
 * Return: void
 */

int _env(char **env, char **head)
{
	int i = 0;

	(void)head;
	(void)env;
	if (!environ)
		return (-1);
	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
return (0);
}

/**
 * mygetenv - Gets an environmental variable from the PATH.
 * @env_var: The environment variable to find.
 * Return: A pointer to the environment variable on success
 * NULL on failure.
 */
char **mygetenv(const char *env_var)
{
	int i, len;

	len = strlen(env_var);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(env_var, environ[i], len) == 0)
			return (&environ[i]);
	}

	return (NULL);
}

/**
 * free_env - frees the environment variables.
 */
void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}
