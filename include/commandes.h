#ifndef COMMANDES_H
#define COMMANDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void executions_user_commandes(char **commandes);
int is_builtin_command(char *argv);
void execute_builtin_command(char **argv);

#endif