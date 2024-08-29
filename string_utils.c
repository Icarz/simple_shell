#include "shell.h"

/**
 * our_strtok - function that return an array of strings
 *@str: string that going to be split
 *@delim: delimiter.
 * Return: doble pointer to a string.
 */

char  **our_strtok(char *str, const char *delim)
{
	int iter, counter = 0, counter2 = 0, counter3 = 0, counter4 = 0, counter5 = 0;
	char **palabras = NULL;

	for (iter = 0; str[iter] != '\0'; iter++)
	{
		if (str[iter] == delim[0])
			counter++;
	}
	counter = counter + 1;
	palabras = malloc(sizeof(char *) * (counter + 1));


	for (iter = 0; iter < counter; iter++)
	{
		while (str[counter2] != delim[0] && str[counter2] != '\0')
		{
			counter2++;
			counter4++;
		}
	*(palabras + iter) = _calloc(sizeof(char), 512);
	counter4 = 0;
	while (str[counter3] != delim[0] && str[counter3] != '\0')
	{
		palabras[iter][counter5] = str[counter3];
		palabras[iter][counter5 + 1] = '\0';
		counter3++;
		counter5++;
	}
	counter2 = counter2 + 1;
	counter3 = counter3 + 1;
	counter5 = 0;
	}
	palabras[iter] = NULL;
	return (palabras);
}
