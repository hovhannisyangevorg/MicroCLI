#include "shell.h"

// #include "builtins.h"

int ft_echo(t_command *command, t_symbol_table* table)
{
    (void)table;

    int is_new_line = 1;
    int option_n = 0;
    size_t i = 0;
    i = 0;
    if (command->argument && command->argument->arguments && command->argument->arguments[0])
    {
        if (command->argument->arguments[1])
        {
            if (command->argument->arguments[1][0] == '-')
            {
                ++i;
                option_n = 0;
                while (command->argument->arguments[1][i])
                {
                    
                    if (command->argument->arguments[1][i] != 'n')
                    {
                        option_n = 1;
                        break;
                    }
                    ++i;
                }
                if (!option_n)
                    is_new_line = 0;
            }
        }
    }
    if (is_new_line)
        i = 1;
    else
        i = 2;
    while (command->argument->arguments[i])
    {
        ft_putstr_fd(command->argument->arguments[i], STDOUT_FILENO);
        if (command->argument->arguments[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        ++i;
    }
    if (is_new_line)
        ft_putchar_fd('\n', STDOUT_FILENO);

    return 0;
}
