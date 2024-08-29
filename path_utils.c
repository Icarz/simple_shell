#include "shell.h"

/**
 * our_strcat - Concatenate 2 strings
 * @dest: First string
 * @src: Second string.
 * Return: Concatenated string.
 */

char *our_strcat(char *dest, char *src)
{
	int counter, iter;

	for (counter = 0; dest[counter]; counter++)
	{}
	for (iter = 0; src[iter]; iter++)
	{
		dest[counter + iter] = src[iter];
	}
	return (dest);
}

/**
 * special_free - Free memory.
 * @cartman: Pointer to be freeded.
 * Return: No return.
 */

void special_free(char **cartman)
{
	int i;

	for (i = 0; *(cartman + i); i++)
	{
		free(*(cartman + i));
	}
	free(cartman);
}

/**
 * add_command_path - Add the command and "/" to the path.
 * @num_path: Number of directories on the PATH.
 * @token_path: Directories on the PATH.
 * @token_line: User input tokenized.
 * Return: No return point.
 */

void add_command_path(int num_path, char **token_path, char **token_line)
{
	int i;

	for (i = 0; i < num_path; i++) /*concatena linea al token*/
	{
		token_path[i] = our_strcat(token_path[i], "/");
		token_path[i] = our_strcat(token_path[i], token_line[0]);
	}
}
