#include "shell.h"


int	ft_exit(t_command *command, t_hash_table* env)
{
    printf("exit\n");
    (void)command;
    (void)env;
    // return 0;
    exit(0);
}


