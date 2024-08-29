#include "simple_shell.h"

/**
 * prepend_node - Adds a node to the beginning of the list
 * @head: Address of pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node, or NULL on failure
 */
list_t *prepend_node(list_t **head, const char *str, int num)
{
    list_t *new_node;

    if (!head)
        return (NULL);
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    new_node->next = *head;
    *head = new_node;
    return (new_node);
}

/**
 * append_node - Adds a node to the end of the list
 * @head: Address of pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node, or NULL on failure
 */
list_t *append_node(list_t **head, const char *str, int num)
{
    list_t *new_node, *current_node;

    if (!head)
        return (NULL);

    current_node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (current_node)
    {
        while (current_node->next)
            current_node = current_node->next;
        current_node->next = new_node;
    }
    else
        *head = new_node;
    return (new_node);
}

/**
 * print_list_strings - Prints only the str element of a list_t linked list
 * @head: Pointer to the first node
 *
 * Return: Number of nodes in the list
 */
size_t print_list_strings(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return (count);
}

/**
 * remove_node_at_index - Deletes a node at a given index
 * @head: Address of pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
    list_t *current_node, *previous_node;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (index == 0)
    {
        current_node = *head;
        *head = (*head)->next;
        free(current_node->str);
        free(current_node);
        return (1);
    }
    current_node = *head;
    while (current_node)
    {
        if (i == index)
        {
            previous_node->next = current_node->next;
            free(current_node->str);
            free(current_node);
            return (1);
        }
        i++;
        previous_node = current_node;
        current_node = current_node->next;
    }
    return (0);
}

/**
 * free_all_nodes - Frees all nodes in a list
 * @head_ptr: Address of pointer to the head node
 *
 * Return: void
 */
void free_all_nodes(list_t **head_ptr)
{
    list_t *current_node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;
    head = *head_ptr;
    current_node = head;
    while (current_node)
    {
        next_node = current_node->next;
        free(current_node->str);
        free(current_node);
        current_node = next_node;
    }
    *head_ptr = NULL;
}
