/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:05:13 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 16:39:18 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char    *ft_get_line()
{
    char	*line;

    line = readline("Minishell $> ");
    if (line)
        add_history(line);
    return (line);
}
