#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SH_RL_BUFSIZE 1024
#define SH_TOK_BUFSIZE 1024
#define SH_TOK_DELIM " \t\r\n\a"
#define UNUSED(x) void(x)

void sh_loop(void);
void sh_loop_non_interactive(void);
char *sh_read_line(void);
char **sh_split_line(char *line);
int sh_execute(char **args);
int sh_launch(char **args);
int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);
int sh_num_builtins();

#endif
