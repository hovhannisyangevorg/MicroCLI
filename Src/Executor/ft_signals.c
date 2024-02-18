/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:00:08 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 15:48:59 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void sigint_handler(int signum)
{
	(void)signum;
	if (g_global_state.minishell_signal != SIGCHILD)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void sigquit_handler(int signum)
{
	(void)signum;
	if (g_global_state.minishell_signal == SIGCHILD)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}