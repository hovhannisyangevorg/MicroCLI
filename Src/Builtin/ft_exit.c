/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:49:33 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/11 20:49:40 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_exit(t_command *command, t_symbol_table* table)
{
    printf("exit\n");
    (void)command;
    (void)table;
    exit(0);
}


