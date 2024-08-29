#include "simple_shell.h"

/**
 * get_history_filepath - Retrieves the path to the history file
 * @info: Pointer to the info_t struct
 *
 * Return: Allocated string containing the path to the history file, or NULL on failure
 */
char *get_history_filepath(info_t *info)
{
char *buffer, *home_directory;

home_directory = _getenv(info, "HOME=");
if (!home_directory)
return (NULL);
buffer = malloc(sizeof(char) * (_strlen(home_directory) + _strlen(HIST_FILE) + 2));
if (!buffer)
return (NULL);
buffer[0] = 0;
_strcpy(buffer, home_directory);
_strcat(buffer, "/");
_strcat(buffer, HIST_FILE);
return (buffer);
}

/**
 * save_history - Creates or appends to the history file
 * @info: Pointer to the info_t struct
 *
 * Return: 1 on success, -1 on failure
 */
int save_history(info_t *info)
{
ssize_t file_descriptor;
char *filepath = get_history_filepath(info);
list_t *node = NULL;

if (!filepath)
return (-1);
file_descriptor = open(filepath, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filepath);
if (file_descriptor == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_putsfd(node->str, file_descriptor);
_putfd('\n', file_descriptor);
}
_putfd(BUF_FLUSH, file_descriptor);
close(file_descriptor);
return (1);
}

/**
 * load_history - Reads history from the file
 * @info: Pointer to the info_t struct
 *
 * Return: Number of history entries on success, 0 on failure
 */
int load_history(info_t *info)
{
int i, last_index = 0, line_count = 0;
ssize_t file_descriptor, read_length, file_size = 0;
struct stat file_stats;
char *buffer = NULL, *filepath = get_history_filepath(info);

if (!filepath)
return (0);
file_descriptor = open(filepath, O_RDONLY);
free(filepath);
if (file_descriptor == -1)
return (0);
if (!fstat(file_descriptor, &file_stats))
file_size = file_stats.st_size;
if (file_size < 2)
return (0);
buffer = malloc(sizeof(char) * (file_size + 1));
if (!buffer)
return (0);
read_length = read(file_descriptor, buffer, file_size);
buffer[file_size] = 0;
if (read_length <= 0)
return (free(buffer), 0);
close(file_descriptor);
for (i = 0; i < file_size; i++)
if (buffer[i] == '\n')
{
buffer[i] = 0;
build_history_list(info, buffer + last_index, line_count++);
last_index = i + 1;
}
if (last_index != i)
build_history_list(info, buffer + last_index, line_count++);
free(buffer);
info->histcount = line_count;
while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);
renumber_history(info);
return (info->histcount);
}

/**
 * build_history_list - Adds an entry to the history linked list
 * @info: Pointer to the info_t struct
 * @buffer: Buffer containing the history entry
 * @line_count: The history line count
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buffer, int line_count)
{
list_t *node = NULL;

if (info->history)
node = info->history;
add_node_end(&node, buffer, line_count);
if (!info->history)
info->history = node;
return (0);
}

/**
 * renumber_history - Renumbers the history linked list after modifications
 * @info: Pointer to the info_t struct
 *
 * Return: The new history count
 */
int renumber_history(info_t *info)
{
list_t *node = info->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}
