#include "shell.h"


int	ft_exit(t_command *command, t_symbol_table* table)
{
    printf("exit\n");
    (void)command;
    (void)table;
    // return 0;
    exit(0);
}


