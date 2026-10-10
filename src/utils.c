// Inclut le header des fonctions utilitaires
#include "../include/utils.h"

/**
 * @brief Vérifie si un token est un symbole de redirection ou de pipe.
 *
 * Les symboles reconnus sont « < », « > », « >> » et « | ».
 *
 * @param token Chaîne à comparer. Elle ne doit pas être NULL.
 * @return 1 si token correspond à un symbole reconnu, 0 sinon.
 */
int is_redirection_or_pipe(char *token)
{
    // Symboles recherchés : entrée (<), sortie (>), sortie en ajout (>>), pipe (|)
    // Le NULL final marque la fin du tableau pour la boucle
    char *symbols[] = {"<", ">", ">>", "|", NULL};

    for (int i = 0; symbols[i] != NULL; i++)
    {
        // Comparaison exacte du mot avec chaque symbole
        if (strcmp(token, symbols[i]) == 0)
            return 1;
    }
    return 0;
}

/**
 * @brief Vérifie si une commande contient une redirection ou un pipe.
 *
 * Parcourt les éléments de command jusqu'à son marqueur final NULL et
 * teste chacun d'eux avec is_redirection_or_pipe().
 *
 * @param command Tableau de chaînes terminé par NULL. Il ne doit pas être NULL.
 * @return 1 si un symbole de redirection ou de pipe est présent, 0 sinon.
 */
int contains_redirection_or_pipe(char **command)
{
    // Parcourt tous les arguments jusqu'au NULL final
    for (int i = 0; command[i] != NULL; i++)
    {
        // Dès qu'un symbole est trouvé, on s'arrête et on renvoie 1
        if (is_redirection_or_pipe(command[i]))
            return 1;
    }
    return 0;
}
