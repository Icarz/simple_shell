#ifndef SHELL_H
#define SHELL_H

#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>

extern char **environ;


void exc_process(char **token_line, char **token_path, char *linea);
void non_interactive_mode(void);
void interactive_mode(void);

/* STRING_UTILS */
char  **our_strtok(char *str, const char *delim);
int count_words(char *str, char *delim);

/* UTILS */
int largo(char *string);
void ultimonulo(char *linea);
char *buscar_path(void);
int num_tokens(char **str);
int _strcmpn(char *s1, char *s2, int n);

/* PATH_UTILS */
char *our_strcat(char *dest, char *src);
void special_free(char **cartman);
void add_command_path(int num_path, char **token_path, char **token_line);

/* MEMORY_AND_SIGNAL */
void *_calloc(unsigned int nmemb, unsigned int size);
void handle_sigint(int sig);
void set_null(char *linea);

/* STRING_UTILS2 */
char *no_spaces(char *linea);
void sys_err(char *av, char *error, char *av_o);

#endif
