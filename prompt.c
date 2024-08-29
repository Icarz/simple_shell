#include "shell.h"

/**
 * prompt - display
 */
void prompt(void)
{
write(STDOUT_FILENO, "#cisfun$ ", 9);
}
