#include "main.h"
/**
 * copyenviron - Creates a copy of the environment.
 * Return: Pointer to the new copy and NULL on fail
 */

char **copyenviron(void)
{
    int i;
	char **_environ;
	size_t size;

	for (size = 0; environ[size]; size++)
		;

	_environ = malloc(sizeof(char *) * (size + 1));
	if (!_environ)
    {
		return (NULL);
    }
	for (i = 0; environ[i]; i++)
	{
		_environ[i] = malloc(strlen(environ[i]) + 1);

		if (!_environ[i])
		{
			for (i--; i >= 0; i--)
				free(_environ[i]);
			free(_environ);
			return (NULL);
		}
		strcpy(_environ[i], environ[i]);
	}
	_environ[i] = NULL;
	return (_environ);
}
