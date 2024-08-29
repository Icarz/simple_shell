#include "simple_shell.h"

/**
 * free_and_nullify - Frees a pointer and sets the address to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0
 */
int free_and_nullify(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}
