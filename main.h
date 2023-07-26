#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

// Function declarations
char *get_env(char *cmd);
void execute_command(char *cmd);
int execute_commands(char *line);
void print_env(void);
void ls_builtin(void);
ssize_t _getline(char **lineptr, size_t *n);
int get_tokens(char *line, char *tokens[], int max_tokens);
void free_tokens(char **tokens);
int set_env(const char *name, const char *value, int overwrite);
int unset_env(const char *name);
void parse_command(char *command, char **argv, int max_tokens);
int some_function_to_get_last_command_exit_status(void);

#endif /* MAIN_H */
