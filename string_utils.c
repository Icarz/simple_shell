#include "simple_shell.h"

/**
 * copy_string - Copies a string
 * @destination: The destination string to be copied to
 * @source: The source string
 * @n: The number of characters to copy
 * 
 * Return: The destination string
 */
char *copy_string(char *destination, const char *source, int n)
{
    int index, fill;
    char *original_dest = destination;

    index = 0;
    while (source[index] != '\0' && index < n - 1)
    {
        destination[index] = source[index];
        index++;
    }
    if (index < n)
    {
        fill = index;
        while (fill < n)
        {
            destination[fill] = '\0';
            fill++;
        }
    }
    return (original_dest);
}

/**
 * concatenate_strings - Concatenates two strings
 * @destination: The first string
 * @source: The second string
 * @n: The maximum number of bytes to use from source
 * 
 * Return: The concatenated string
 */
char *concatenate_strings(char *destination, const char *source, int n)
{
    int dest_len, src_index;
    char *original_dest = destination;

    dest_len = 0;
    while (destination[dest_len] != '\0')
        dest_len++;
    
    src_index = 0;
    while (source[src_index] != '\0' && src_index < n)
    {
        destination[dest_len] = source[src_index];
        dest_len++;
        src_index++;
    }
    if (src_index < n)
        destination[dest_len] = '\0';
    
    return (original_dest);
}

/**
 * find_character - Locates a character in a string
 * @str: The string to be searched
 * @ch: The character to look for
 * 
 * Return: A pointer to the first occurrence of the character, or NULL if not found
 */
char *find_character(const char *str, char ch)
{
    while (*str)
    {
        if (*str == ch)
            return (char *)str;
        str++;
    }
    return (NULL);
}
