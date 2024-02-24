/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2024/02/18 22:04:01 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_global_state	g_global_state;

void	ft_program(char **env)
{
	t_container		container;

	container.table = ft_create_symbol_table(env);
	g_global_state.argument = ft_get_env(container.table->env, "_");
	ft_get_pid(container, container.table->env);
	ft_init_global_state();
	ft_main_loop(&container);
	clear_history();
	ft_clear_symbol_table(container.table);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_program(env);
	return (0);
}
