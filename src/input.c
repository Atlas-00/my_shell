// Inclut le header lié au traitement de l'entrée utilisateur
#include "../include/input.h"

// Nombre maximum d'éléments dans le tableau d'arguments (dernier slot réservé au NULL)
#define MAX_ARGS 64

// Découpe la ligne saisie en mots (séparés par des espaces)
// Renvoie un tableau de pointeurs terminé par NULL, ou NULL en cas d'erreur
char **parsing_user_input(char *input)
{
    // Vérifie qu'on a bien reçu une ligne
    if (input == NULL)
    {
        fprintf(stderr, "Erreur : input est NULL\n");
        return NULL;
    }

    // Alloue le tableau qui contiendra les pointeurs vers chaque argument
    char **argv = malloc(sizeof(char *) * MAX_ARGS);
    if (argv == NULL)
    {
        // Échec de l'allocation mémoire : message d'erreur système et abandon
        perror("Erreur : L'allocation à échoué\n");
        return NULL;
    }

    int args = 0; // Compteur d'arguments déjà stockés

    // strtok découpe la chaîne sur les espaces : premier appel avec la chaîne
    // Attention : strtok MODIFIE input (remplace les espaces par des '\0'),
    // donc argv pointe à l'intérieur de input, il n'y a pas de copie
    char *str_token = strtok(input, " ");
    while (str_token != NULL)
    {
        // On garde une place pour le NULL final : si le tableau est plein, on abandonne
        if (args >= MAX_ARGS - 1)
        {
            fprintf(stderr, "Erreur : trop d'arguments (limite = %d)\n", MAX_ARGS);
            free(argv);
            return NULL;
        }

        argv[args] = str_token;        // Range le mot trouvé dans le tableau
        str_token = strtok(NULL, " "); // Mot suivant (NULL = on continue sur la même chaîne)
        args++;
    }

    // Termine le tableau par NULL, comme l'exige execvp
    argv[args] = NULL;
    return argv;
}