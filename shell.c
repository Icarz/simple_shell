#include "shell.h"

/**
 * main - main of project shell
 * Return: No return
 */

int main(void)
{
	if (!(isatty(STDIN_FILENO)))
		non_interactive_mode();
	else
		interactive_mode();
	return (0);
}
