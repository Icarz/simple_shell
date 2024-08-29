#include "simple_shell.h"

/**
 * string_copy - Copies a string from source to destination
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: Pointer to the destination buffer
 */
char *string_copy(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * string_duplicate - Duplicates a given string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *string_duplicate(const char *str)
{
int length = 0;
char *dup_str;

if (str == NULL)
return (NULL);
while (*str++)
length++;
dup_str = malloc(sizeof(char) * (length + 1));
if (!dup_str)
return (NULL);
for (length++; length--;)
dup_str[length] = *--str;
return (dup_str);
}

/**
 * print_string - Prints a string to standard output
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
write_char(str[i]);
i++;
}
}

/**
 * write_char - Writes a character to standard output
 * @c: The character to print
 *
 * Return: On success 1, on error -1, and errno is set appropriately.
 */
int write_char(char c)
{
static int buf_index;
static char buffer[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
{
write(1, buffer, buf_index);
buf_index = 0;
}
if (c != BUF_FLUSH)
buffer[buf_index++] = c;
return (1);
}
