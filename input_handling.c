#include "simple_shell.h"

/**
 * buffer_input - Buffers chained commands
 * @info: Parameter struct
 * @buffer: Address of buffer
 * @length: Address of length variable
 *
 * Return: Bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length)
{
ssize_t bytes_read = 0;
size_t length_ptr = 0;
if (!*length) /* If nothing left in the buffer, fill it */
{
free(*buffer);
*buffer = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
bytes_read = getline(buffer, &length_ptr, stdin);
#else
bytes_read = custom_getline(info, buffer, &length_ptr);
#endif
if (bytes_read > 0)
{
if ((*buffer)[bytes_read - 1] == '\n')
{
(*buffer)[bytes_read - 1] = '\0'; /* Remove trailing newline */
bytes_read--;
}
info->linecount_flag = 1;
remove_comments(*buffer);
build_history_list(info, *buffer, info->histcount++);
{
*length = bytes_read;
info->cmd_buf = buffer;
}
}
}
return (bytes_read);
}

/**
 * fetch_input - Gets a line minus the newline
 * @info: Parameter struct
 *
 * Return: Bytes read
 */
ssize_t fetch_input(info_t *info)
{
static char *buffer; /* The ';' command chain buffer */
static size_t index, end, length;
ssize_t bytes_read = 0;
char **buffer_ptr = &(info->arg), *pointer;

_putchar(BUF_FLUSH);
bytes_read = buffer_input(info, &buffer, &length);
if (bytes_read == -1) /* EOF */
return (-1);
if (length) /* We have commands left in the chain buffer */
{
end = index; /* Init new iterator to current buffer position */
pointer = buffer + index; /* Get pointer for return */

check_chain(info, buffer, &end, index, length);
while (end < length) /* Iterate to semicolon or end */
{
if (is_chain(info, buffer, &end))
break;
end++;
}

index = end + 1; /* Increment past nulled ';' */
if (index >= length) /* Reached end of buffer? */
{
index = length = 0; /* Reset position and length */
info->cmd_buf_type = CMD_NORM;
}

*buffer_ptr = pointer; /* Pass back pointer to current command position */
return (_strlen(pointer)); /* Return length of current command */
}

*buffer_ptr = buffer; /* Else not a chain, pass back buffer from custom_getline() */
return (bytes_read); /* Return length of buffer from custom_getline() */
}

/**
 * read_buffer - Reads a buffer
 * @info: Parameter struct
 * @buffer: Buffer
 * @index: Size
 *
 * Return: Bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *index)
{
ssize_t bytes_read = 0;

if (*index)
return (0);
bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
if (bytes_read >= 0)
*index = bytes_read;
return (bytes_read);
}

/**
 * custom_getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: Size of the line
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
static char buffer[READ_BUF_SIZE];
static size_t index, buf_length;
size_t size;
ssize_t bytes_read = 0, line_size = 0;
char *p = NULL, *new_ptr = NULL, *newline;
p = *ptr;
if (p && length)
line_size = *length;
if (index == buf_length)
index = buf_length = 0;
bytes_read = read_buffer(info, buffer, &buf_length);
if (bytes_read == -1 || (bytes_read == 0 && buf_length == 0))
return (-1);
newline = find_character(buffer + index, '\n');
size = newline ? 1 + (unsigned int)(newline - buffer) : buf_length;
new_ptr = _realloc(p, line_size, line_size ? line_size + size : size + 1);
if (!new_ptr) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (line_size)
concatenate_strings(new_ptr, buffer + index, size - index);
else
copy_string(new_ptr, buffer + index, size - index + 1);
line_size += size - index;
index = size;
p = new_ptr;
if (length)
*length = line_size;
*ptr = p;
return (line_size);
}

/**
 * sigintHandler - Handles SIGINT (Ctrl-C)
 * @signal_number: The signal number
 *
 * Return: Void
 */
void sigintHandler(__attribute__((unused))int signal_number)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
