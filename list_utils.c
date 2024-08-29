#include "simple_shell.h"

/**
 * get_list_length - Determines the length of a linked list
 * @head: Pointer to the first node
 *
 * Return: Number of nodes in the list
 */
size_t get_list_length(const list_t *head)
{
size_t length = 0;

while (head)
{
head = head->next;
length++;
}
return (length);
}

/**
 * convert_list_to_strings - Returns an array of strings from list->str
 * @head: Pointer to the first node
 *
 * Return: Array of strings, or NULL on failure
 */
char **convert_list_to_strings(list_t *head)
{
list_t *current_node = head;
size_t list_size = get_list_length(head), i;
char **string_array;
char *string;

if (!head || !list_size)
return (NULL);
string_array = malloc(sizeof(char *) * (list_size + 1));
if (!string_array)
return (NULL);
for (i = 0; current_node; current_node = current_node->next, i++)
{
string = malloc(_strlen(current_node->str) + 1);
if (!string)
{
for (size_t j = 0; j < i; j++)
free(string_array[j]);
free(string_array);
return (NULL);
}
string = _strcpy(string, current_node->str);
string_array[i] = string;
}
string_array[i] = NULL;
return (string_array);
}

/**
 * print_list_elements - Prints all elements of a list_t linked list
 * @head: Pointer to the first node
 *
 * Return: Number of nodes in the list
 */
size_t print_list_elements(const list_t *head)
{
size_t count = 0;

while (head)
{
_puts(convert_number(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_putchar('\n');
head = head->next;
count++;
}
return (count);
}

/**
 * find_node_starting_with - Returns node whose string starts with the prefix
 * @head: Pointer to the list head
 * @prefix: String to match
 * @next_char: The next character after the prefix to match, or -1 for any
 *
 * Return: Matching node or NULL if not found
 */
list_t *find_node_starting_with(list_t *head, char *prefix, char next_char)
{
char *p = NULL;

while (head)
{
p = starts_with(head->str, prefix);
if (p && (next_char == -1 || *p == next_char))
return (head);
head = head->next;
}
return (NULL);
}

/**
 * get_node_index - Gets the index of a specific node
 * @head: Pointer to the list head
 * @node: Pointer to the node
 *
 * Return: Index of the node, or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t index = 0;

while (head)
{
if (head == node)
return (index);
head = head->next;
index++;
}
return (-1);
}
