/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2024/02/18 22:04:01 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_global_state	g_global_state;
int ft_sig()
{
	return 0;
}
void ft_init_global_state()
{
	g_global_state.is_tree = 0;
	g_global_state.last_in = -1;
	g_global_state.heredoc_signal = -1;
	g_global_state.permission_status = 0;
	rl_catch_signals = 0;
	g_global_state.is_dir = 0;
	rl_signal_event_hook = &ft_sig;
}

void ft_init_start_state()
{

}


void	ft_program(char **env)
{
	t_container		container;
	char 			*line;
	t_list_token	*list;

	list = NULL;
	
	container.table = ft_create_symbol_table(env);
	g_global_state.argument = ft_get_env(container.table->env, "_");
	ft_get_pid(container, container.table->env);
	tcgetattr(STDIN_FILENO, &g_global_state.orig_termios);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	while (1)
	{
		g_global_state.minishell_signal = SIGNORMAL;
		line = ft_get_line();
		if (!line)
			exit(0);
		if (!(*line))
		{
			free(line);
			continue;
		}
		int status = ft_balanced(line);
		if (status)
		{
			container.exit_status = status;
			ft_update_env_exit(container, container.table);
			free(line);
			continue;
		}
		list = ft_tokenize(line, SEPARATORS);
		container = ft_parser(container, list);
		if (container.exit_status == SUCCESS_CODE)
			ft_executor(container.table, container);
		else
		{
			close(container.fd.error);
			close(container.fd.input);
			close(container.fd.output);
			ft_update_env_exit(container, container.table);
		}
		if (container.exec_type == LIST)
		{
			// TODO: hendle free when argunemt is NULL.
			// ft_free_command(container.command);
		}
		else
		{
			// ft_free_tree(container.tree->ast_node);	
			// free(container.tree);
		}
		ft_free_list(list);
		free(line);
    }
    clear_history();
	ft_clear_symbol_table(container.table);
}


// echo ''
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_program(env);
	return (0);	
}
