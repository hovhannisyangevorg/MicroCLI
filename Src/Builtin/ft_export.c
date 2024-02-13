/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:49:46 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/11 20:49:47 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_export(t_command* command, t_symbol_table* table)
{
	(void)command;
	t_hash_table_arr arr = ft_sort_env(table->env);
	print_env_table(arr);
	free(arr.table);
	(void)command;
	return(0);
}
