#include "shell.h"
#include <unistd.h>
/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
char *command;
char *args[] = {NULL, NULL};
int status;
while (1) 
{
printf("#cisfun$ ");
read = getline(&line, &len, stdin);
if (read == -1)
{
if (feof(stdin))
{
printf("\n");
exit(EXIT_SUCCESS);
}
else
{
perror("getline");
exit(EXIT_FAILURE);
}
}
if (line[read - 1] == '\n')
line[read - 1] = '\0';
command = strtok(line, " \t");
args[0] = command;
pid_t pid = fork();
if (pid == -1) 
{
perror("fork");
exit(EXIT_FAILURE);
} 
else if (pid == 0) 
{
if (execve(command, args, environ) == -1) 
{
perror(command);
exit(EXIT_FAILURE);
}
} 
else 
{
waitpid(pid, &status, 0);
}
}
free(line);
return 0;
}
