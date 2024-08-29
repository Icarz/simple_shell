#include "simple_shell.h"

/**
 * fetch_environ - Returns the string array copy of our environment
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * 
 * Return: Pointer to the environment string array
 */
char **fetch_environ(info_t *info)
{
    if (!info->environment || info->env_modified)
    {
        info->environment = list_to_strings(info->env_list);
        info->env_modified = 0;
    }

    return (info->environment);
}

/**
 * remove_env_var - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: The environment variable to remove
 * 
 * Return: 1 on successful deletion, 0 otherwise
 */
int remove_env_var(info_t *info, char *variable)
{
    list_t *node = info->env_list;
    size_t index = 0;
    char *pos;

    if (!node || !variable)
        return (0);

    while (node)
    {
        pos = starts_with(node->str, variable);
        if (pos && *pos == '=')
        {
            info->env_modified = delete_node_at_index(&(info->env_list), index);
            index = 0;
            node = info->env_list;
            continue;
        }
        node = node->next;
        index++;
    }
    return (info->env_modified);
}

/**
 * add_or_modify_env_var - Initializes a new environment variable,
 *                         or modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: The environment variable name
 * @value: The environment variable value
 * 
 * Return: Always 0
 */
int add_or_modify_env_var(info_t *info, char *variable, char *value)
{
    char *buffer = NULL;
    list_t *node;
    char *pos;

    if (!variable || !value)
        return (0);

    buffer = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buffer)
        return (1);
    _strcpy(buffer, variable);
    _strcat(buffer, "=");
    _strcat(buffer, value);
    node = info->env_list;
    while (node)
    {
        pos = starts_with(node->str, variable);
        if (pos && *pos == '=')
        {
            free(node->str);
            node->str = buffer;
            info->env_modified = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env_list), buffer, 0);
    free(buffer);
    info->env_modified = 1;
    return (0);
}
