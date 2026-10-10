// Inclut le header des fonctions utilitaires
#include "../include/utils.h"

// Indique si un mot est un symbole de redirection ou de pipe
// Renvoie 1 si oui, 0 sinon
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

// Indique si une commande (tableau d'arguments terminé par NULL)
// contient au moins un symbole de redirection ou de pipe
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
