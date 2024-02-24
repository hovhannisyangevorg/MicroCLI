/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:00:08 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 19:05:12 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	if (g_global_state.minishell_signal != SIGCHILD)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_sigquit_handler(int signum)
{
	(void)signum;
	if (g_global_state.minishell_signal == SIGCHILD)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	ft_child_sigint(int num)
{
	(void)num;
	if (g_global_state.heredoc_signal == -1)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
	}
}

void	ft_heredoc_signal(int num)
{
	if (num == SIGINT)
	{
		g_global_state.heredoc_signal = num;
		g_global_state.minishell_signal = SIGHEREDOC;
		close(STDIN_FILENO);
	}
}

int	ft_sig(void)
{
	return (0);
}
