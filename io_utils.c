#include "simple_shell.h"

/**
 * print_error_message - Prints an input string to stderr
 * @message: The string to be printed
 *
 * Return: Nothing
 */
void print_error_message(char *message)
{
int index = 0;

if (!message)
return;
while (message[index] != '\0')
{
write_char_to_stderr(message[index]);
index++;
}
}

/**
 * write_char_to_stderr - Writes a character to stderr
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_char_to_stderr(char character)
{
static int buffer_index;
static char buffer[WRITE_BUF_SIZE];
if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
{
write(2, buffer, buffer_index);
buffer_index = 0;
}
if (character != BUF_FLUSH)
buffer[buffer_index++] = character;
return (1);
}

/**
 * write_char_to_fd - Writes a character to a given file descriptor
 * @character: The character to print
 * @file_descriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_char_to_fd(char character, int file_descriptor)
{
static int buffer_index;
static char buffer[WRITE_BUF_SIZE];
if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
{
write(file_descriptor, buffer, buffer_index);
buffer_index = 0;
}
if (character != BUF_FLUSH)
buffer[buffer_index++] = character;
return (1);
}
/**
 * print_string_to_fd - Prints an input string to a given file descriptor
 * @string: The string to be printed
 * @file_descriptor: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_string_to_fd(char *string, int file_descriptor)
{
int count = 0;
if (!string)
return (0);
while (*string)
{
count += write_char_to_fd(*string++, file_descriptor);
}
return (count);
}
