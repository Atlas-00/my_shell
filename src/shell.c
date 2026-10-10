// Inclut le header principal du shell (qui doit amener stdio, stdlib, readline, etc.)
#include "../include/shell.h"

// Taille maximale d'un chemin de répertoire (en octets) pour le buffer getcwd
#define PATH_MAX 4096

/**
 * @brief Exécute la boucle principale du shell.
 *
 * Affiche le répertoire courant dans le prompt, lit les commandes saisies
 * avec readline(), puis les découpe en arguments. Les commandes intégrées
 * sont exécutées dans le processus du shell ; les autres sont lancées
 * comme des commandes système.
 *
 * La boucle se termine si getcwd() échoue ou si readline() indique la fin
 * de l'entrée. La commande intégrée « exit » peut également terminer
 * le programme.
 *
 * @return Cette fonction ne retourne aucune valeur.
 */
void shell_loop()
{
    char *input;           // Ligne tapée par l'utilisateur (allouée par readline)
    char buffer[PATH_MAX]; // Stocke le répertoire courant pour l'afficher dans le prompt

    // Boucle infinie : on ne sort que via la commande "exit" ou une erreur de getcwd
    while (1)
    {
        // Récupère le répertoire courant dans buffer
        // Si ça marche, on l'affiche (sans retour à la ligne) comme début de prompt
        if (getcwd(buffer, sizeof(buffer)) != NULL)
            printf("%s", buffer);
        else
        {
            // getcwd a échoué : on affiche l'erreur système et on quitte la boucle
            perror("getcwd() erreur");
            return;
        }

        // Affiche ":~$ " et lit la ligne saisie par l'utilisateur
        // (avec historique et édition de ligne grâce à readline)
        input = readline(" :~$ ");

        if (input == NULL)
        {
            printf("Fin du programme \n");
            return;
        }
        else if (strcmp(input, "") == 0)
        {
            free(input);
            continue;
        }
        else
        {
            // Découpe la ligne en tableau d'arguments (argv[0] = commande, argv[1..] = arguments)
            char **argv = parsing_user_input(input);

            if (argv == NULL || argv[0] == NULL)
            {
                free(argv);
                continue;
            }

            // Si la commande fait partie de celles codées dans le shell (exit, cd, help)
            if (is_builtin_command(argv[0]))
            {
                // On l'exécute directement dans le processus du shell
                execute_builtin_command(argv);
            }
            else
            {
                // Sinon, c'est une commande système (ls, pwd...) : on la lance dans un processus enfant
                executions_user_commandes(argv);
            }
        }
    }
}
