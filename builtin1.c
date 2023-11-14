/**
 * print_list - Prints a linked list.
 * @headOfList: Pointer to the head of the list.
 * Return: Always 0.
 */
int print_list(list_t *headOfList)
{
	while (headOfList)
	{
	_puts(headOfList->str);
	headOfList = headOfList->next;
	}
	return (0);
}

/**
 * delete_node_at_index - Deletes node at index.
 * @headOfList: Pointer to the head of the list.
 * @index: Index of the node to delete.
 * Return: 0 on success, -1 on failure.
 */
int delete_node_at_index(list_t **headOfList, unsigned int index)
{
	list_t *current = *headOfList;
	list_t *next;

	if (*headOfList == NULL)
	return (-1);

	if (index == 0)
	{
	*headOfList = current->next;
	free(current);
	return (0);
	}

	for (unsigned int i = 0; i < index - 1; i++)
	{
	if (current->next == NULL)
	return (-1);
	current = current->next;
	}

	next = current->next->next;
	free(current->next);
	current->next = next;

	return (0);
}

