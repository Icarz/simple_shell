#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>

#define MAX_ARGS 64
#define MAX_COMMAND_LENGTH 1024
#define MAX_PATH_LENGTH 4096

extern char **environ;
char *get_full_path(const char *command);
void execute1(char **argv);
ssize_t read_command(char *command);
void execute_command(char *command);
char *_strcat1(char *dest, const char *src);
int check_exit(char *input);
int check_blank(char *input);
int check_env(char *input);
void print_environment(void);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen1(const char *s);
char **split_string(char *str, const char *delim);

#endif
