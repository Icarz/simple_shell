#include "shell.h"



/**
 * interactive_mode - main of project shell
 * Return: No return
 */


void interactive_mode(void)
{
	char **token_path = 0, **token_line = NULL;
	char *my_propmt = "#U# ", *texto, *linea = NULL;
	size_t  largo_linea = 0;
	const char *delim = " ";
	int num_path;
	ssize_t readline = 0;
	int counter = 0;

signal(SIGINT, handle_sigint);

	while (readline != EOF)
	{
		write(STDOUT_FILENO, my_propmt, largo(my_propmt));
		counter++;
		readline = getline(&linea, &largo_linea, stdin);
		if (readline == EOF)
		{
			write(STDIN_FILENO, "\n", 1);
			continue;
		}

		if (*linea == 10)
		continue;

		ultimonulo(linea);
		linea = no_spaces(linea);
		texto = buscar_path();
		token_path = our_strtok(texto, ":");
		num_path = num_tokens(token_path);
		token_line = our_strtok(linea, delim);
		add_command_path(num_path, token_path, token_line);
		exc_process(token_line, token_path, linea);
		special_free(token_path);
		special_free(token_line);
	}


free(linea);
}
