#include "../include/shell.h"

void shell_loop()
{
    char input[1024];

    while (1)
    {
        printf("> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        // Parsing 
        input[strcspn(input, "\n")] = 0;
        char **argv = parsing_user_input(input);

        executions_user_commandes(argv);
    }
}
