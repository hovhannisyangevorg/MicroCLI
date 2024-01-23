/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:05:13 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/20 18:05:16 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


void	sig_handler_c(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

char    *ft_get_line()
{
    char	*line;

    line = readline("Minishell $> ");
    if (line)
        add_history(line);
    return (line);
}
