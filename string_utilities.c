#include "simple_shell.h"

/**
 * string_length - Returns the length of a string
 * @str: The string whose length to check
 *
 * Return: Integer length of the string
 */
int string_length(char *str)
{
int length = 0;

if (!str)
return (0);

while (*str++)
length++;
return (length);
}

/**
 * string_compare - Performs lexicographic comparison of two strings.
 * @str1: The first string
 * @str2: The second string
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int string_compare(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with_substring - Checks if a string starts with a given substring
 * @main_str: The string to search
 * @substr: The substring to find
 *
 * Return: Address of the next character in main_str after the match, or NULL
 */
char *starts_with_substring(const char *main_str, const char *substr)
{
while (*substr)
if (*substr++ != *main_str++)
return (NULL);
return ((char *)main_str);
}

/**
 * string_concat - Concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *string_concat(char *dest, char *src)
{
char *result = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (result);
}
