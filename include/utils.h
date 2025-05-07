#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int is_redirection_or_pipe(char *token);
int contains_redirection_or_pipe(char **command);

#endif