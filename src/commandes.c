#include "../include/commandes.h"

void executions_user_commandes(char **argv)
{
    __pid_t pid = fork();

    if (pid == 0)
    {
        int test_exe = execvp(argv[0], argv);
        if (test_exe == -1)
        {
            perror("Commande iconnue !");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    }

    free(argv);
}