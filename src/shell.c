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

        if (is_builtin_command(argv[0]))
        {
            execute_builtin_command(argv);
        }
        else
        {
            executions_user_commandes(argv);
        }
    }
}
