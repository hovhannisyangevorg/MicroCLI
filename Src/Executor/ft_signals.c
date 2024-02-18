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

void ft_sigquit_handler(int signum)
{
	(void)signum;
	if (g_global_state.minishell_signal == SIGCHILD)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void ft_child_sigint(int num)
{
	(void)num;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);
}

void ft_heredoc_signal(int num)
{
	g_global_state.heredoc_signal = num;
	g_global_state.minishell_signal = SIGNORMAL;
	close(STDIN_FILENO);
}