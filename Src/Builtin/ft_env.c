/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:49:26 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/11 20:49:27 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_env(t_command *command, t_symbol_table *table)
{
	(void)command;
	(void)table;
	print_env(table->env, VENV);
	return (EXIT_SUCCESS);
}
