#include "shell.h"


//TODO handle arguments and non-numerics
int	ft_exit(t_command *command, t_symbol_table* table)
{
    printf("exit\n");
    (void)command;
    (void)table;
    int i = ft_atoi(command->argument->arguments[1]);
    // return 0;
    exit(i % 255);
}


