#include "simple_shell.h"

/**
 * is_chain_delimiter - Checks if the current character in the buffer is a chain delimiter.
 * @info: The parameter struct containing shell information
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 *
 * Return: 1 if a chain delimiter is found, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buffer, size_t *position)
{
size_t index = *position;
if (buffer[index] == '|' && buffer[index + 1] == '|')
{
buffer[index] = '\0';
index++;
info->cmd_buf_type = CMD_OR;
}
else if (buffer[index] == '&' && buffer[index + 1] == '&')
{
buffer[index] = '\0';
index++;
info->cmd_buf_type = CMD_AND;
}
else if (buffer[index] == ';') /* End of this command */
{
buffer[index] = '\0'; /* Replace semicolon with null character */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*position = index;
return (1);
}

/**
 * continue_chain - Determines whether to continue chaining commands based on the last status.
 * @info: The parameter struct containing shell information
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 * @start_index: Starting position in the buffer
 * @buffer_length: Length of the buffer
 *
 * Return: Void
 */
void continue_chain(info_t *info, char *buffer, size_t *position, size_t start_index, size_t buffer_length)
{
size_t index = *position;
if (info->cmd_buf_type == CMD_AND)
{
if (info->status != 0)
{
buffer[start_index] = '\0';
index = buffer_length;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (info->status == 0)
{
buffer[start_index] = '\0';
index = buffer_length;
}
}
*position = index;
}

/**
 * replace_alias_in_args - Replaces aliases in the tokenized argument list.
 * @info: The parameter struct containing shell information
 *
 * Return: 1 if any alias is replaced, 0 otherwise
 */
int replace_alias_in_args(info_t *info)
{
int attempt;
list_t *alias_node;
char *alias_value;
for (attempt = 0; attempt < 10; attempt++)
{
alias_node = node_starts_with(info->alias, info->argv[0], '=');
if (!alias_node)
return (0);
free(info->argv[0]);
alias_value = _strchr(alias_node->str, '=');
if (!alias_value)
return (0);
alias_value = _strdup(alias_value + 1);
if (!alias_value)
return (0);
info->argv[0] = alias_value;
}
return (1);
}
/**
 * replace_variables_in_args - Replaces shell variables in the tokenized argument list.
 * @info: The parameter struct containing shell information
 *
 * Return: 1 if any variable is replaced, 0 otherwise
 */
int replace_variables_in_args(info_t *info)
{
int arg_index;
list_t *env_node;
for (arg_index = 0; info->argv[arg_index]; arg_index++)
{
if (info->argv[arg_index][0] != '$' || !info->argv[arg_index][1])
continue;
if (!_strcmp(info->argv[arg_index], "$?"))
{
replace_string(&(info->argv[arg_index]), _strdup(convert_number(info->status, 10, 0)));
continue;
}
if (!_strcmp(info->argv[arg_index], "$$"))
{
replace_string(&(info->argv[arg_index]), _strdup(convert_number(getpid(), 10, 0)));
continue;
}
env_node = node_starts_with(info->env, &info->argv[arg_index][1], '=');
if (env_node)
{
replace_string(&(info->argv[arg_index]), _strdup(_strchr(env_node->str, '=') + 1));
continue;
}
replace_string(&info->argv[arg_index], _strdup(""));
}
return (0);
}

/**
 * replace_string - Replaces the value of a string with a new string.
 * @old_string: Address of the old string
 * @new_string: The new string to replace with
 *
 * Return: 1 if the string is replaced, 0 otherwise
 */
int replace_string(char **old_string, char *new_string)
{
free(*old_string);
*old_string = new_string;
return (1);
}
