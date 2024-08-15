#include "shell.h"
#include <string.h>

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
 * main - Entry point for the simple shell (with arguments)
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
while (1) 
{
_puts("#cisfun$ ");
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
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
if (execve(argv[0], argv, environ) == -1)
{
perror(argv[0]);
exit(EXIT_FAILURE);
}
}
else
{
waitpid(pid, NULL, 0);
free(argv);
}
}
}
free(line);
return (0);
}
