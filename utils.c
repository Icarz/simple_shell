#include "shell.h"

/**
 * largo - function that return size of a string
 *@string: string that going to be measure
 * Return: int size of string.
 */

int largo(char *string)
{
	int cont_car;

	for (cont_car = 0; *(string + cont_car) != '\0'; cont_car++)
	;
	return (cont_car);
}

/**
 * ultimonulo - function that change the last character (enter for null)
 *@linea: string that going to be measure
 * Return: zero.
 */

void ultimonulo(char *linea)
{
	int i;

	for (i = 0; *(linea + i); i++)
	{
	if (*(linea + i) == 10)
		*(linea + i) = 0;
	}
}

/**
 * buscar_path - function that find the path and storage  in a double pointer
 * Return: zero.
 */

char *buscar_path(void)
{
	char *texto = NULL, *path = "PATH";
	int i, n, r;

	n = 4;

	for (i = 0; environ[i] != NULL; i++)
	{
		r = _strcmpn(path, environ[i], n);
		if (r == 0)
		{
			texto = environ[i] + 5;
		}
	}
	return (texto);
}

/**
 * num_tokens - function that find the path and storage in a double pointer
 *@str: string that going to be measure
 * Return: zero.
 */

int num_tokens(char **str)
{
	int num_path;

	for (num_path = 0; str[num_path] != NULL; num_path++)
	;
	return (num_path);
}

/**
 *_strcmpn - check 2 strings.
 *@s1: variable
 *@s2: variable
 *@n: number of characters
 * Return: Always m.
 */
int _strcmpn(char *s1, char *s2, int n)
{
	int m, i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			m = s1[i] - s2[i];
			return (m);
		}
	}
return (0);
}
