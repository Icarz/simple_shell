#include "shell.h"

/**
 * non_interactive_mode - main of project shell
 * Return: No return.
 */

void non_interactive_mode(void)
{
char **token_path = NULL;
char **token_line = NULL;
char *texto, *linea = NULL;
size_t largo_linea = 0;
const char *delim = " ";
int num_path;

getline(&linea, &largo_linea, stdin);
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
free(linea);
exit(0);
}
