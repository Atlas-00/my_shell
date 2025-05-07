#include "../include/shell.h"

#define PATH_MAX 4096

void shell_loop()
{
    char *input;
    char buffer[PATH_MAX];

    while (1)
    {
        if (getcwd(buffer, sizeof(buffer)) != NULL)
            printf("%s", buffer);
        else
        {
            perror("getcwd() erreur");
            return;
        }

        input = readline(":~$ ");

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
