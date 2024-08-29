#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for reading and writing */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining types */
#define CMD_NORMAL   0
#define CMD_OR        1
#define CMD_AND       2
#define CMD_CHAIN     3

/* Number conversion flags */
#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED  2

/* Flags to indicate getline() or strtok() usage */
#define USE_GETLINE_FUNCTION 0
#define USE_STRTOK_FUNCTION 0

#define HISTORY_FILE ".simple_shell_history"
#define MAX_HISTORY 4096

extern char **global_environ;

/**
 * struct node - Singly linked list node
 * @index: Index of the node
 * @data: Data string
 * @next: Pointer to the next node
 */
typedef struct node
{
	int index;
	char *data;
	struct node *next;
} node_t;

/**
 * struct shell_info - Contains pseudo-arguments for function calls
 * @input: Command input string
 * @arguments: Array of arguments parsed from input
 * @cmd_path: Path to the current command
 * @arg_count: Number of arguments
 * @line_number: Line number for error tracking
 * @error_code: Error code for exit() calls
 * @line_count_flag: Flag to indicate if the line should be counted
 * @prog_name: Name of the program
 * @environment: Linked list copy of environment variables
 * @history: Linked list of command history
 * @alias: Linked list of command aliases
 * @custom_environ: Custom copy of environment variables
 * @history_changed: Flag indicating if history was modified
 * @exit_status: Status code of the last executed command
 * @command_buffer: Pointer to command buffer for chaining
 * @command_type: Type of command (e.g., ||, &&, ;)
 * @input_fd: File descriptor for input reading
 * @history_count: Count of history lines
 */
typedef struct shell_info
{
	char *input;
	char **arguments;
	char *cmd_path;
	int arg_count;
	unsigned int line_number;
	int error_code;
	int line_count_flag;
	char *prog_name;
	node_t *environment;
	node_t *history;
	node_t *alias;
	char **custom_environ;
	int history_changed;
	int exit_status;

	char **command_buffer; /* Buffer for command chaining */
	int command_type; /* Type of command chaining */
	int input_fd;
	int history_count;
} shell_info_t;

#define SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct built_in - Contains a built-in command and its handler
 * @cmd_name: Name of the built-in command
 * @handler: Function to handle the command
 */
typedef struct built_in
{
	char *cmd_name;
	int (*handler)(shell_info_t *);
} built_in_table;

/* shell_main.c */
int shell_loop(shell_info_t *, char **);
int locate_builtin(shell_info_t *);
void execute_command(shell_info_t *);
void create_process(shell_info_t *);

/* shell_parser.c */
int check_command(shell_info_t *, char *);
char *duplicate_substring(char *, int, int);
char *resolve_path(shell_info_t *, char *, char *);

/* shell_utils.c */
int shell_utils_main(char **);

/* shell_errors.c */
void print_error_message(char *);
int print_char_error(char);
int print_fd_char(char c, int fd);
int print_fd_string(char *str, int fd);

/* shell_string.c */
int string_length(char *);
int string_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *string_concat(char *, char *);

/* shell_string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int print_character(char);

/* shell_exit.c */
char *string_n_copy(char *, char *, int);
char *string_n_concat(char *, char *, int);
char *find_char_in_string(char *, char);

/* shell_tokenizer.c */
char **split_string(char *, char *);
char **split_string_by_delimiter(char *, char);

/* shell_realloc.c */
char *memory_set(char *, char, unsigned int);
void free_string_array(char **);
void *resize_memory(void *, unsigned int, unsigned int);

/* shell_memory.c */
int free_memory(void **);

/* shell_atoi.c */
int is_interactive(shell_info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_int(char *);

/* shell_errors1.c */
int convert_to_int(char *);
void print_error_info(shell_info_t *, char *);
int print_decimal(int, int);
char *convert_to_string(long int, int, int);
void remove_comment_from_string(char *);

/* shell_builtin.c */
int builtin_exit(shell_info_t *);
int builtin_cd(shell_info_t *);
int builtin_help(shell_info_t *);

/* shell_builtin1.c */
int builtin_history(shell_info_t *);
int builtin_alias(shell_info_t *);

/* shell_getline.c */
ssize_t get_input_line(shell_info_t *);
int getline_function(shell_info_t *, char **, size_t *);
void handle_signal_interrupt(int);

/* shell_getinfo.c */
void clear_shell_info(shell_info_t *);
void set_shell_info(shell_info_t *, char **);
void release_shell_info(shell_info_t *, int);

/* shell_environ.c */
char *get_environment_variable(shell_info_t *, const char *);
int builtin_env(shell_info_t *);
int builtin_setenv(shell_info_t *);
int builtin_unsetenv(shell_info_t *);
int populate_environment_list(shell_info_t *);

/* shell_getenv.c */
char **retrieve_environ(shell_info_t *);
int unset_environment_variable(shell_info_t *, char *);
int set_environment_variable(shell_info_t *, char *, char *);

/* shell_history.c */
char *get_history_file_path(shell_info_t *info);
int save_history(shell_info_t *info);
int load_history(shell_info_t *info);
int build_history_list(shell_info_t *info, char *buf, int line_count);
int renumber_history_lines(shell_info_t *info);

/* shell_lists.c */
node_t *add_list_node(node_t **, const char *, int);
node_t *append_list_node(node_t **, const char *, int);
size_t print_list_strings(const node_t *);
int remove_node_at_index(node_t **, unsigned int);
void free_list_nodes(node_t **);

/* shell_lists1.c */
size_t get_list_length(const node_t *);
char **convert_list_to_strings(node_t *);
size_t display_list(const node_t *);
node_t *find_node_starting_with(node_t *, char *, char);
ssize_t get_node_index(node_t *, node_t *);

/* shell_vars.c */
int is_command_chain(shell_info_t *, char *, size_t *);
void check_command_chain(shell_info_t *, char *, size_t *, size_t, size_t);
int process_alias(shell_info_t *);
int process_variables(shell_info_t *);
int replace_string_content(char **, char *);

#endif
