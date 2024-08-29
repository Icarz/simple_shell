#include "simple_shell.h"

/**
 * builtin_env - Displays the current environment variables
 * @info: Pointer to the shell_info_t structure
 *
 * Return: Always 0
 */
int builtin_env(shell_info_t *info)
{
	print_list_str(info->environment);
	return (0);
}

/**
 * get_env_value - Retrieves the value of an environment variable
 * @info: Pointer to the shell_info_t structure
 * @variable_name: Name of the environment variable
 *
 * Return: Value of the environment variable, or NULL if not found
 */
char *get_env_value(shell_info_t *info, const char *variable_name)
{
	list_t *node = info->environment;
	char *value;

	while (node)
	{
		value = starts_with(node->str, variable_name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * builtin_setenv - Initializes or modifies an environment variable
 * @info: Pointer to the shell_info_t structure
 *
 * Return: Always 0 on success, 1 on error
 */
int builtin_setenv(shell_info_t *info)
{
	if (info->arguments_count != 3)
	{
		print_error("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(info, info->arguments[1], info->arguments[2]))
		return (0);
	return (1);
}

/**
 * builtin_unsetenv - Removes an environment variable
 * @info: Pointer to the shell_info_t structure
 *
 * Return: Always 0
 */
int builtin_unsetenv(shell_info_t *info)
{
	int i;

	if (info->arguments_count == 1)
	{
		print_error("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i < info->arguments_count; i++)
		unset_env(info, info->arguments[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list
 * @info: Pointer to the shell_info_t structure
 *
 * Return: Always 0
 */
int populate_env_list(shell_info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->environment = node;
	return (0);
}
