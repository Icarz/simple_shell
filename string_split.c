#include "simple_shell.h"

/**
 * split_string - Splits a string into words using delimiters. Repeat delimiters are ignored.
 * @str: The input string to split
 * @delim: The delimiter string
 * Return: Pointer to an array of strings, or NULL on failure
 */
char **split_string(char *str, char *delim)
{
int i, word_index, word_length, char_index, word_count = 0;
char **words_array;
if (str == NULL || str[0] == '\0')
return (NULL);
if (!delim)
delim = " ";
/* Count the number of words */
for (i = 0; str[i] != '\0'; i++)
if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || str[i + 1] == '\0'))
word_count++;
if (word_count == 0)
return (NULL);
/* Allocate memory for the array of strings */
words_array = malloc((word_count + 1) * sizeof(char *));
if (!words_array)
return (NULL);
for (i = 0, word_index = 0; word_index < word_count; word_index++)
{
while (is_delim(str[i], delim))
i++;
word_length = 0;
while (!is_delim(str[i + word_length], delim) && str[i + word_length])
word_length++;
words_array[word_index] = malloc((word_length + 1) * sizeof(char));
if (!words_array[word_index])
{
for (word_length = 0; word_length < word_index; word_length++)
free(words_array[word_length]);
free(words_array);
return (NULL);
}
for (char_index = 0; char_index < word_length; char_index++)
words_array[word_index][char_index] = str[i++];
words_array[word_index][char_index] = '\0';
}
words_array[word_index] = NULL;
return (words_array);
}

/**
 * split_string_by_char - Splits a string into words using a single character delimiter.
 * @str: The input string to split
 * @delim: The delimiter character
 * Return: Pointer to an array of strings, or NULL on failure
 */
char **split_string_by_char(char *str, char delim)
{
int i, word_index, word_length, char_index, word_count = 0;
char **words_array;
if (str == NULL || str[0] == '\0')
return (NULL);
/* Count the number of words */
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != delim && str[i + 1] == delim) ||
(str[i] != delim && str[i + 1] == '\0') || str[i + 1] == delim)
word_count++;
if (word_count == 0)
return (NULL);
/* Allocate memory for the array of strings */
words_array = malloc((word_count + 1) * sizeof(char *));
if (!words_array)
return (NULL);
for (i = 0, word_index = 0; word_index < word_count; word_index++)
{
while (str[i] == delim)
i++;
word_length = 0;
while (str[i + word_length] != delim && str[i + word_length])
word_length++;
words_array[word_index] = malloc((word_length + 1) * sizeof(char));
if (!words_array[word_index])
{
for (word_length = 0; word_length < word_index; word_length++)
free(words_array[word_length]);
free(words_array);
return (NULL);
}
for (char_index = 0; char_index < word_length; char_index++)
words_array[word_index][char_index] = str[i++];
words_array[word_index][char_index] = '\0';
}
words_array[word_index] = NULL;
return (words_array);
}
