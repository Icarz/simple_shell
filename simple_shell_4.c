#include "shell.h"
#include <string.h>

/**
 * find_command_path - Finds the full path of a command using the PATH
 * @command: The command to find
 *
 * Return: The full path of the command, or NULL if not found
 */
char *find_command_path(char *command)
{
    char *path_env = getenv("PATH");
    char *path_copy = strdup(path_env);
    char *path_token;
    char *full_path;

    path_token = strtok(path_copy, ":");
    while (path_token != NULL)
    {
        full_path = malloc(strlen(path_token) + strlen(command) + 2);
        if (full_path == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        strcpy(full_path, path_token);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        path_token  
 = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/**
 * _puts - Prints a string to stdout
 * @str: The string to print
 */
void _puts(char *str)
{
    while (*str)
    {
        write(STDOUT_FILENO, str, 1);
        str++;
    }
}

/**
 * strtow - Splits a string into an array of words
 * @str: The string to split
 * @delim: The delimiter characters
 *
 * Return: An array of strings (words), or NULL on failure
 */
char **strtow(char *str, char *delim)
{
    char *token;
    char **words = NULL;
    int num_words = 0;
    int i;

    if (str == NULL || str[0] == '\0')
        return (NULL);

    token = strtok(str, delim);
    while (token != NULL)
    {
        num_words++;
        token = strtok(NULL, delim);
    }

    words = malloc((num_words + 1) * sizeof(char *));
    if (words == NULL)
        return (NULL);

    token = strtok(str, delim);
    for (i = 0; i < num_words; i++)
    {
        words[i] = strdup(token);
        token = strtok(NULL, delim);
    }
    words[num_words] = NULL;

    return (words);
}

/**
 * is_builtin - Checks if a command is a built-in
 * @command: The command to check
 *
 * Return: 1 if it's a built-in, 0 otherwise
 */
int is_builtin(char *command)
{
    if (strcmp(command, "exit") == 0)
        return 1;
    return 0;
}

/**
 * handle_builtin - Executes a built-in command
 * @argv: Array of arguments (command and its arguments)
 *
 * Return: 0 on success, 1 on failure
 */
int handle_builtin(char **argv)
{
    if (strcmp(argv[0], "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }

    return 1;
}

/**
 * main - Entry point for the simple shell (with arguments, PATH, and exit)
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
    info_t info[] = { INFO_INIT };
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **argv = NULL;
    char *full_path;

    while (1)
    {
        _puts(":) ");
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin))
            {
                _puts("\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        line[strcspn(line, "\n")] = 0;

        argv = strtow(line, " ");
        if (argv == NULL)
        {
            perror("strtow");
            exit(EXIT_FAILURE);
        }

        if (argv[0] != NULL)
        {
            if (is_builtin(argv[0]))
            {
                handle_builtin(argv);
            }
            else
            {
                full_path = find_command_path(argv[0]);

                if (full_path != NULL)
                {
                    pid_t pid = fork();
                    if (pid == -1)
                    {
                        perror("fork");
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        if (execve(full_path, argv, environ) == -1)
                        {
                            perror(argv[0]);
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        waitpid(pid, NULL, 0);
                        free(full_path);
                    }
                }
                else
                {
                    fprintf(stderr, "%s: command not found\n", argv[0]);
                }
            }

            free(argv);
        }
    }

    free(line);
    return (0);
}
