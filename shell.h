#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#define MAX_ARGUMENTS 10
#define BUFFER_SIZE 1024
#define MAX_LINES 256
extern char **environ;
int printAlpha(void);
void prompt(void);
char *my_strcpy(char *desti, const char *sou);
ssize_t get_line(char **line, size_t *p, FILE *obj);
int print_env(void);
void exec(char **argv);
char *path_command(char *com);
char *my_strcat(char *desti, char *sou);
int my_strlen(char *string);
unsigned int vali_char(char t, const char *string);
char *str_to(char *st, const char *dlim);
int my_strcmp(char *string1, char *string2);

#endif
