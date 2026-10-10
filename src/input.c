#include "../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Nombre maximum d'arguments, sans compter le NULL final. */
#define MAX_ARGS 64

/**
 * @brief Découpe une ligne de commande en arguments.
 *
 * Sépare la ligne aux espaces, tabulations et retours à la ligne.
 * strtok() modifie la chaîne input en remplaçant les séparateurs par '\0' ;
 * les chaînes pointées par argv restent donc dans la mémoire de input.
 *
 * @param input Ligne à découper. Elle doit être modifiable.
 * @return Tableau d'arguments terminé par NULL, ou NULL si input est NULL,
 *         si la ligne ne contient aucun argument ou en cas d'erreur.
 *         Le tableau retourné doit être libéré avec free().
 */
char **parsing_user_input(char *input)
{
    /* Une chaîne NULL ne peut pas être découpée. */
    if (input == NULL)
    {
        fprintf(stderr, "Erreur : input est NULL\n");
        return NULL;
    }

    /* Réserve de la place pour MAX_ARGS pointeurs, NULL final compris. */
    char **argv = malloc(sizeof(char *) * MAX_ARGS);
    if (argv == NULL)
    {
        perror("Erreur d'allocation de argv");
        return NULL;
    }

    int args = 0;

    /* strtok modifie input et renvoie chaque argument l'un après l'autre. */
    char *str_token = strtok(input, " \t\n");

    while (str_token != NULL)
    {
        /* Garde une case pour le NULL final. */
        if (args >= MAX_ARGS - 1)
        {
            fprintf(stderr, "Erreur : trop d'arguments (maximum : %d)\n",
                    MAX_ARGS - 1);
            free(argv);
            return NULL;
        }

        argv[args] = str_token;
        args++;

        str_token = strtok(NULL, " \t\n");
    }

    /* Une ligne vide ou composée seulement de séparateurs ne contient aucun argument. */
    if (args == 0)
    {
        free(argv);
        return NULL;
    }

    /* execvp() attend un tableau terminé par NULL. */
    argv[args] = NULL;
    return argv;
}
