#include "simple_shell.h"

/**
 * fill_memory - Fills a memory area with a constant byte.
 * @memory: Pointer to the memory area.
 * @byte: The byte to fill the memory with.
 * @n: The number of bytes to fill.
 *
 * Return: Pointer to the memory area.
 */
char *fill_memory(char *memory, char byte, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        memory[i] = byte;
    return (memory);
}

/**
 * free_string_array - Frees an array of strings.
 * @string_array: The array of strings to free.
 */
void free_string_array(char **string_array)
{
    char **temp = string_array;

    if (!string_array)
        return;
    while (*string_array)
        free(*string_array++);
    free(temp);
}

/**
 * reallocate_memory - Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: The size of the previous block in bytes.
 * @new_size: The size of the new block in bytes.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return (malloc(new_size));
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == old_size)
        return (ptr);

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return (new_ptr);
}
