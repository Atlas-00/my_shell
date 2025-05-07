#include "../include/input.h"

#define MAX_ARGS 64

char **parsing_user_input(char *input)
{
    if (input == NULL)
    {
        fprintf(stderr, "Erreur : input est NULL\n");
        return NULL;
    }

    char **argv = malloc(sizeof(char *) * MAX_ARGS);
    if (argv == NULL)
    {
        perror("Erreur : L'allocation à échoué\n");
        return NULL;
    }

    int args = 0;
    char *str_token = strtok(input, " ");
    while (str_token != NULL)
    {
        if (args >= MAX_ARGS - 1)
        {
            fprintf(stderr, "Erreur : trop d'arguments (limite = %d)\n", MAX_ARGS);
            free(argv);
            return NULL;
        }

        argv[args] = str_token;
        str_token = strtok(NULL, " ");
        args++;
    }
    argv[args] = NULL;
    return argv;
}
