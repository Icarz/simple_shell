#include "simple_shell.h"

/**
 * builtin_exit - Exits the shell with a given status
 * @info: Pointer to the shell_info_t structure
 * 
 * Return: -2 to indicate the shell should exit, 1 if an error occurred
 */
int builtin_exit(shell_info_t *info)
{
	int exit_status;

	if (info->arguments[1])  /* If there is an exit argument */
	{
		exit_status = string_to_int(info->arguments[1]);
		if (exit_status == -1)
		{
			info->exit_status = 2;
			print_error_info(info, "Illegal number: ");
			print_error_message(info->arguments[1]);
			print_char_error('\n');
			return (1);
		}
		info->error_code = string_to_int(info->arguments[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}

/**
 * builtin_cd - Changes the current directory of the process
 * @info: Pointer to the shell_info_t structure
 * 
 * Return: Always 0
 */
int builtin_cd(shell_info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int change_dir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		print_error_message("TODO: >>getcwd failure error message here<<\n");
	if (!info->arguments[1])
	{
		target_dir = get_environment_variable(info, "HOME=");
		if (!target_dir)
			change_dir_result = chdir((target_dir = get_environment_variable(info, "PWD=")) ? target_dir : "/");
		else
			change_dir_result = chdir(target_dir);
	}
	else if (string_compare(info->arguments[1], "-") == 0)
	{
		if (!get_environment_variable(info, "OLDPWD="))
		{
			print_error_message(current_dir);
			print_char_error('\n');
			return (1);
		}
		print_error_message(get_environment_variable(info, "OLDPWD="));
		print_char_error('\n');
		change_dir_result = chdir((target_dir = get_environment_variable(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		change_dir_result = chdir(info->arguments[1]);
	if (change_dir_result == -1)
	{
		print_error_info(info, "can't cd to ");
		print_error_message(info->arguments[1]);
		print_char_error('\n');
	}
	else
	{
		set_environment_variable(info, "OLDPWD", get_environment_variable(info, "PWD="));
		set_environment_variable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * builtin_help - Displays a help message
 * @info: Pointer to the shell_info_t structure
 * 
 * Return: Always 0
 */
int builtin_help(shell_info_t *info)
{
	char **args;

	args = info->arguments;
	print_error_message("Help functionality is not yet implemented\n");
	if (0)
		print_error_message(*args); /* Temporary workaround for unused variable */
	return (0);
}
