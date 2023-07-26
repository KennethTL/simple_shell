#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define PROMPT "#shell$ "
#define BUF_SIZE 1024

void exec(char **argv);
char *get_env(char *cmd);
void execute_command(char *cmd, char **argv);
void print_env(void);
void ls_builtin(void);
ssize_t _getline(char **lineptr, size_t *n);
int get_tokens(char *line, char *tokens[], int max_tokens);
void free_tokens(char **tokens);
int set_env(const char *name, const char *value, int overwrite);
int unset_env(const char *name);

#endif /* SHELL_H */
