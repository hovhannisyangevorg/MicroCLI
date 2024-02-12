#include "shell.h"


int	ft_unset(t_command* command, t_symbol_table* table)
{
	if (command->argument && command->argument->arguments && command->argument->arguments[0] && command->argument->arguments[1])
		ft_pop_entity(table->env, command->argument->arguments[1]);

	return(0);
}
