#include <unistd.h>
#include "main.h"
#include <string.h>
/*STRING FUNCTIONS TO BE IMPLEMENTED strcpy, strcat,strncat, strlen*/

/**
 * append_cwd- appends the current working directory to the path dirs
 * @dirpath: the directories from the PATH separated by ':'
 * Return: a path with all colons replaced by cwd
 */
char *append_cwd(char *dirpath)
{
	char *dirpath_cpy, *cwd;
	int i, len = 0;

	cwd = *(mygetenv("PWD")) + 4;/*implement this function*/
	for (i = 0; dirpath[i]; i++)
	{
		if (dirpath[i] == ':')
		{
			if (i == 0 ||dirpath[i +1] == ':' || dirpath[i +1] == '\0')
				len += strlen(cwd) + 1;
			else
				len++;
		}
		else
			len++;

	}
	dirpath_cpy = malloc(sizeof(char) * (len+ 1));/*len + 1*/
	if (!dirpath_cpy)
		return (NULL);
	dirpath_cpy[0] = '\0';
	for (i = 0; dirpath[i]; i++)
	{
		if (dirpath[i] == ':')
		{
			if (i == 0)
			{
				strcat(dirpath_cpy, cwd);
				strcat(dirpath_cpy, ":");
			}
			else if (dirpath[i + 1] == ':' || dirpath[i + 1] == '\0')
			{
				strcat(dirpath_cpy, ":");
				strcat(dirpath_cpy, cwd);
			}
			else
				strcat(dirpath_cpy, ":");

		}
		else
			strncat(dirpath_cpy, &dirpath[i], 1);
	}
	return (dirpath_cpy);
}
/**
 * tokenize_path: parses the PATH env variable and tokenizes them based on the ':'
 * @dirpath: list of PATH directories
 * Return: a linked list containing all the path directories
 */
linkedlist_t *tokenize_path(char *dirpath)
{
	linkedlist_t *head;
	char **dir, *dirpath_cpy;
	int i = 0;

	dirpath_cpy = append_cwd(dirpath);
	if (!dirpath_cpy)
		return (NULL);
	dir = mystrtok(dirpath_cpy, ":");
	free(dirpath_cpy);
	if (!dir)
		return (NULL);
	for (i = 0; dir[i]; i++)
		if (add_node_end(&head, dir[i]) == NULL)
		{
			free_linked_list(head);
			free(dir);
			return (NULL);
		}
	free(dir);
	return (head);

}
/**
 * find_command_in_path- finds a command in the PATH environment variable
 * @command: the command to be be found in the path
 * Return: the full_path to the command, NULL onm failure
 */
char *find_command_in_path(char *command)
{
	char **path, *temp;
	linkedlist_t *pathdir, *head;
	struct stat s;

	path = mygetenv("PATH");/*implement the getenv function*/
	if (!path || !(*path))
		return (NULL);
	pathdir = tokenize_path(*path + 5);
	head = pathdir;

	while (pathdir)
	{
		temp = malloc(strlen(pathdir->path) + strlen(command) + 2);
		if (!temp)
			return (NULL);

		strcpy(temp, pathdir->path);
		strcat(temp, "/");
		strcat(temp, command);

		if (stat(temp, &s) == 0)
		{
			free_linked_list(head);/*Implement the free linked_list function*/
			return (temp);
		}
		pathdir = pathdir->next;
		free(temp);
	}
	free_linked_list(head);/*Implement the free linked_list function*/

	return (NULL);
}
