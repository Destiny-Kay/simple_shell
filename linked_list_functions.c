#include "main.h"

/**
 * add_node_end - Adds a new node at the end of a linked list.
 * @head: A pointer to the head of the list_t list.
 * @dirpath: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
linkedlist_t *add_node_end(linkedlist_t **head, char *dirpath)
{
	linkedlist_t *new_node = malloc(sizeof(linkedlist_t));
	linkedlist_t *last;

	if (!new_node)
		return (NULL);
	new_node->path = dirpath;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * free_linked_list - Frees linked list DS.
 * @head: head of linked list.
 */
void free_linked_list(linkedlist_t *head)
{
	linkedlist_t *next;

	while (head)
	{
		next = head->next;
		free(head->path);
		free(head);
		head = next;
	}
}

