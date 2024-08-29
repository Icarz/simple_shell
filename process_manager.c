#include "shell.h"
#include <sys/stat.h>

/**
 * exc_process - Free memory.
 * @token_line: line splited into tokens
 * @token_path: path splited into tokens
 * @linea: user line to be freed
 * Return: No return.
 */

void exc_process(char **token_line, char **token_path, char *linea)
{
	int i = 0;
	pid_t process_exce;
	struct stat st;

	if (stat(token_line[0], &st) == 0)
	{
	process_exce = fork();
	wait(NULL);
		if (process_exce == 0)
		{
			execve(token_line[0], token_line, environ);
		}

	}
	else
	{
	process_exce = fork();
	wait(NULL);
		if (process_exce == 0)
		{
			for (i = 0; token_path[i]; i++)
			{
				if (stat(token_path[i], &st) == 0)
				{
				execve(token_path[i], token_line, environ);
				}
			}
			sys_err(token_line[0], "not found", token_line[0]);
			special_free(token_path);
			special_free(token_line);
			free(linea);
			exit(0);
		}
	}
}

/**
 * sys_err - Set error mesages
 * @av: Arguments
 * @error: Error mesage.
 * @av_o: Arguments.
 * Return: No return.
 */

void sys_err(char *av, char *error, char *av_o)
{
	write(STDERR_FILENO, av_o, largo(av_o));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, av, largo(av));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, largo(error));
	write(STDERR_FILENO, "\n", 1);
}
