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

#endif /* SHELL_H */
