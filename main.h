#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

// Function declarations
char *get_env(char *cmd);
void execute_command(char *cmd, char **argv);
void print_env(void);
void ls_builtin(void);
ssize_t _getline(char **lineptr, size_t *n);
int get_tokens(char *line, char *tokens[], int max_tokens);
void free_tokens(char **tokens);

#endif /* MAIN_H */
