/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:49:33 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/13 20:41:45 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//TODO handle arguments and non-numerics
int	ft_exit(t_command *command, t_symbol_table* table)
{
    printf("exit\n");
    (void)command;
    (void)table;
    int i = ft_atoi(command->argument->arguments[1]);
    exit(i % 255);
}


