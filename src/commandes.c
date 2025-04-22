#include "../include/commandes.h"

void executions_user_commandes(char **argv)
{
    for (int i = 0; argv[i] != NULL; i++)
    {
        printf("%s\n", argv[i]);
    }
}