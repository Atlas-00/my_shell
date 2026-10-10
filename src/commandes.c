// Inclut le header lié à l'exécution des commandes
#include "../include/commandes.h"

// Lance une commande système dans un processus enfant et attend qu'elle se termine
void executions_user_commandes(char **argv)
{
    // Duplique le processus : pid == 0 dans l'enfant, pid > 0 dans le parent, pid < 0 si erreur
    pid_t pid = fork();

    if (pid == 0)
    {
        // Code de l'enfant : remplace le processus par la commande demandée
        // execvp cherche la commande dans le PATH et utilise argv comme arguments
        // Si ça réussit, cette ligne ne retourne jamais
        int test_exe = execvp(argv[0], argv);
        if (test_exe == -1)
        {
            // execvp a échoué (commande introuvable, etc.) : message puis fin de l'enfant
            perror("Commande iconnue !");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        // Code du parent : attend la fin de l'enfant (sans récupérer son code de retour)
        wait(NULL);
    }
    else
    {
        // fork a échoué : on affiche l'erreur et on quitte tout le shell
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    }

    // Libère le tableau d'arguments alloué dans parsing_user_input
    free(argv);
}

// Indique si la commande est un builtin (codé dans le shell lui-même)
// Renvoie 1 si oui, 0 sinon
int is_builtin_command(char *command)
{
    // Liste des commandes gérées en interne
    char *builtin_command[3] = {"exit", "cd", "help"};
    for (int i = 0; i < 3; i++)
    {
        // strcmp renvoie 0 si les deux chaînes sont identiques
        if (strcmp(builtin_command[i], command) == 0)
            return 1;
    }

    return 0;
}

// Exécute un builtin dans le processus du shell
void execute_builtin_command(char **argv)
{
    // Commande "cd" : change le répertoire courant du shell
    if (strcmp(argv[0], "cd") == 0)
    {
        // Pas d'argument après "cd" : on affiche une erreur et on revient au prompt
        if (argv[1] == NULL)
        {
            fprintf(stderr, "Erreur : chemin manquant pour cd\n");
            return;
        }

        // Change de répertoire (le retour de chdir n'est pas vérifié)
        chdir(argv[1]);
    }

    // Commande "exit" : termine le shell
    else if (strcmp(argv[0], "exit") == 0)
    {
        printf("Exit \n");
        exit(0);
    }
    // Commande "help" : affiche la liste des commandes disponibles
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
        // Cas de secours : commande non reconnue comme builtin, on la lance comme commande système
        executions_user_commandes(argv);
    }
}