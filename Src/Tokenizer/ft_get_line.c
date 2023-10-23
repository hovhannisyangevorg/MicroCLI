/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armhakob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:05:13 by gevorg            #+#    #+#             */
/*   Updated: 2023/10/23 20:31:58 by armhakob         ###   ########.fr       */
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
