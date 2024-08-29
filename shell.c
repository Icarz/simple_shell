#include "shell.h"

/**
 * main - code for entry point of the shell
 * Return: 0 on success,or exit on failur.
**/
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
pid_t pid;
char *args[2];

while (1)
{
prompt();
nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
exit(EXIT_SUCCESS);
}
line[nread - 1] = '\0';
args[0] = line;
args[1] = NULL;
pid = fork();
if (pid == -1)
{
perror("./shell");
free(line);
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execve(args[0], args, environ);
perror("./shell");
free(line);
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
free(line);
return (0);
}
