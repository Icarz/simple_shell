#include "shell.h"

/**
 *_calloc-function that allocates memory for an array, using malloc
 *@size: size
 *@nmemb: amount of elements
 *
 *Return: Null or other thing
 **/
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *p;
	unsigned int n;

	if (nmemb == 0 || size == 0)
		return (NULL);

	p = malloc(size * nmemb);

	if (p == NULL)
		return (NULL);
	for (n = 0; n < nmemb * size; n++)
		p[n] = 0;
	return (p);
}

/**
 * handle_sigint - Free memory.
 * @a: line splited into tokens
 * Return: No return.
 */

void handle_sigint(int __attribute__((unused)) a)
{
	char *my_propmt = "#U# ";

	write(STDIN_FILENO, "\n", 1);
	write(STDOUT_FILENO, my_propmt, largo(my_propmt));
}
