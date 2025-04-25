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

int is_builtin_command(char *command)
{
    char *builtin_command[3] = {"exit", "cd", "help"};
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(builtin_command[i], command) == 0)
            return 1;
    }
    
    return 0;
}

void execute_builtin_command(char **argv)
{
    if (strcmp(argv[0], "cd") == 0)
    {
        if (argv[1] == NULL)
        {
            fprintf(stderr, "Erreur : chemin manquant pour cd\n");
            return;
        }

        chdir(argv[1]);
    }
    
    else if (strcmp(argv[0], "exit") == 0)
    {
        printf("Exit \n");
        exit(0);
    }
    else if (strcmp(argv[0], "help") == 0)
    {
        printf("MiniShell - Liste des commandes disponibles :\n");
        printf("  cd [chemin]    : changer de répertoire\n");
        printf("  exit           : quitter le shell\n");
        printf("  help           : afficher ce message d'aide\n");
        printf("  [commande]     : exécute une commande système (ls, pwd, etc.)\n");
    }
    else
    {
        executions_user_commandes(argv);
    }
}