#include "simple_shell.h"

/**
 * is_interactive - Checks if the shell is running in interactive mode
 * @info: Pointer to the shell_info_t structure
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(shell_info_t *info)
{
	return (isatty(STDIN_FILENO) && info->input_fd <= 2);
}

/**
 * is_delimiter - Checks if a character is in the delimiter string
 * @c: Character to check
 * @delimiters: String containing delimiters
 * 
 * Return: 1 if c is a delimiter, 0 otherwise
 */
int is_delimiter(char c, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - Checks if a character is alphabetic
 * @c: Character to check
 * 
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_int - Converts a string to an integer
 * @s: String to convert
 * 
 * Return: Converted integer value, or 0 if no numbers are found
 */
int string_to_int(char *s)
{
	int i, sign = 1, state = 0, result = 0;

	for (i = 0; s[i] != '\0' && state != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			state = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if (state == 1)
			state = 2;
	}

	return (sign * result);
}
