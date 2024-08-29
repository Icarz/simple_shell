#include "simple_shell.h"

/**
 * initialize_info - Initializes info_t struct
 * @info: Pointer to the struct to initialize
 */
void initialize_info(info_t *info)
{
    info->argument = NULL;
    info->argument_vector = NULL;
    info->path = NULL;
    info->argument_count = 0;
}

/**
 * populate_info - Sets up the info_t struct with initial values
 * @info: Pointer to the struct to populate
 * @args: Argument vector
 */
void populate_info(info_t *info, char **args)
{
    int i = 0;

    info->file_name = args[0];
    if (info->argument)
    {
        info->argument_vector = strtow(info->argument, " \t");
        if (!info->argument_vector)
        {
            info->argument_vector = malloc(sizeof(char *) * 2);
            if (info->argument_vector)
            {
                info->argument_vector[0] = _strdup(info->argument);
                info->argument_vector[1] = NULL;
            }
        }
        for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
            ;
        info->argument_count = i;

        replace_aliases(info);
        replace_variables(info);
    }
}

/**
 * release_info - Frees fields in the info_t struct
 * @info: Pointer to the struct to free
 * @all: If true, frees all fields
 */
void release_info(info_t *info, int all)
{
    ffree(info->argument_vector);
    info->argument_vector = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->command_buffer)
            free(info->argument);
        if (info->environment)
            free_list(&(info->environment));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environment_copy);
        info->environment_copy = NULL;
        bfree((void **)info->command_buffer);
        if (info->read_fd > 2)
            close(info->read_fd);
        _putchar(BUF_FLUSH);
    }
}
