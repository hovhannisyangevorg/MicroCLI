#include "shell.h"

int	ft_history(t_command *command, t_symbol_table *table)
{
	size_t	i;

	(void)command;
	(void)table;
	i = 0;
	while (i < g_global_state.history.size)
	{
		ft_putnbr_fd(i, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putendl_fd(g_global_state.history.lines[i], STDOUT_FILENO);
		++i;
	}
	return (EXIT_SUCCESS);
}
