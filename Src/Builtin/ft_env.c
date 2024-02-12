#include "shell.h"

int	ft_env(t_command* command, t_symbol_table* table)
{

    (void)command;
    (void)table;
	print_env(table->env, VENV);
	return(0);
}
