#include "../include/utils.h"

int is_redirection_or_pipe(char *token)
{
    char *symbols[] = {"<", ">", ">>", "|", NULL};

    for (int i = 0; symbols[i] != NULL; i++)
    {
        if (strcmp(token, symbols[i]) == 0)
            return 1;
    }
    return 0;
}

int contains_redirection_or_pipe(char **command)
{
    for (int i = 0; command[i] != NULL; i++)
    {
        if (is_redirection_or_pipe(command[i]))
            return 1;
    }
    return 0;
}
