#include "simple_shell.h"

/**
 * builtin_history - Displays the command history list with line numbers
 * @info: Pointer to the shell_info_t structure
 *
 * Return: Always 0
 */
int builtin_history(shell_info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias from the list
 * @info: Pointer to the shell_info_t structure
 * @alias_str: The alias string to remove
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(shell_info_t *info, char *alias_str)
{
	char *delimiter_pos, original_char;
	int result;

	delimiter_pos = find_char(alias_str, '=');
	if (!delimiter_pos)
		return (1);
	original_char = *delimiter_pos;
	*delimiter_pos = 0;
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*delimiter_pos = original_char;
	return (result);
}

/**
 * add_alias - Adds a new alias or updates an existing one
 * @info: Pointer to the shell_info_t structure
 * @alias_str: The alias string to add or update
 *
 * Return: Always 0 on success, 1 on error
 */
int add_alias(shell_info_t *info, char *alias_str)
{
	char *delimiter_pos;

	delimiter_pos = find_char(alias_str, '=');
	if (!delimiter_pos)
		return (1);
	if (!*++delimiter_pos)
		return (remove_alias(info, alias_str));

	remove_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * display_alias - Prints the alias string in the format key='value'
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int display_alias(list_t *node)
{
	char *delimiter_pos = NULL, *alias = NULL;

	if (node)
	{
		delimiter_pos = find_char(node->str, '=');
		for (alias = node->str; alias <= delimiter_pos; alias++)
			print_char(*alias);
		print_char('\'');
		print_string(delimiter_pos + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * builtin_alias - Handles alias commands
 * @info: Pointer to the shell_info_t structure
 *
 * Return: Always 0
 */
int builtin_alias(shell_info_t *info)
{
	int i = 0;
	char *delimiter_pos = NULL;
	list_t *node = NULL;

	if (info->arguments_count == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->arguments[i]; i++)
	{
		delimiter_pos = find_char(info->arguments[i], '=');
		if (delimiter_pos)
			add_alias(info, info->arguments[i]);
		else
			display_alias(node_starts_with(info->alias, info->arguments[i], '='));
	}

	return (0);
}
