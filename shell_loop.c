#include "simple_shell.h"

/**
 * shell_loop - Main shell loop
 * @info: Parameter and return info struct
 * @argv: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **argv)
{
ssize_t input_status = 0;
int builtin_status = 0;
while (input_status != -1 && builtin_status != -2)
{
clear_info(info);
if (is_interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
input_status = get_input(info);
if (input_status != -1)
{
set_info(info, argv);
builtin_status = find_builtin_command(info);
if (builtin_status == -1)
find_and_execute_command(info);
}
else if (is_interactive(info))
_putchar('\n');
free_info(info, 0);
}
save_history(info);
free_info(info, 1);
if (!is_interactive(info) && info->status)
exit(info->status);
if (builtin_status == -2)
{
if (info->error_code == -1)
exit(info->status);
exit(info->error_code);
}
return (builtin_status);
}

/**
 * find_builtin_command - Finds and executes a builtin command
 * @info: Parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_command(info_t *info)
{
int i, status = -1;
builtin_table builtins[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};
for (i = 0; builtins[i].name; i++)
{
if (_strcmp(info->argv[0], builtins[i].name) == 0)
{
info->line_count++;
status = builtins[i].function(info);
break;
}
}
return (status);
}

/**
 * find_and_execute_command - Finds a command in PATH and executes it
 * @info: Parameter and return info struct
 *
 * Return: void
 */
void find_and_execute_command(info_t *info)
{
char *path = NULL;
int i, non_delim_count = 0;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0; info->argv[i]; i++)
if (!is_delim(info->argv[i], " \t\n"))
non_delim_count++;
if (!non_delim_count)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
execute_command(info);
}
else
{
if ((is_interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
execute_command(info);
else if (*(info->argv) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}
/**
 * execute_command - Forks and executes a command
 * @info: Parameter and return info struct
 *
 * Return: void
 */
void execute_command(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: Add error handling function */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: Add error handling function */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
