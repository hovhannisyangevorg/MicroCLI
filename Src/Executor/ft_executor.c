/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:21:12 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 18:45:26 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_execut_command(t_io io, t_command *command, t_symbol_table* table, t_vector *pipe_fd, size_t pipe_iter)
{
	int						status;
	t_function_callback		biltin_func;
	t_hash_table_arr		env;
	t_vector				fd_vector;

	status = 0;
	g_global_state.is_dir = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);
	signal(SIGINT, SIG_IGN);
	g_global_state.permission_status = SUCCESS_CODE;
	env = ft_convert_env_to_args(table->env, 1, 0);
	ft_expand_env(command, table);

	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) 
	{
		rl_catch_signals = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		g_global_state.permission_status = 0;
		ft_init_arrey(&fd_vector, 0);
		ft_open_file(command, table->env, &fd_vector, io);

		ft_handle_redirect_ios(command->io);
		ft_hendle_pipe(pipe_fd, pipe_iter, command->io);
		if (!command->argument->arguments)
			biltin_func = NULL;
		else
			biltin_func =  ft_get_function(table->function, command->argument->arguments[0]);
		if (biltin_func)
		{
			int status = biltin_func(command, table);
			exit(status);
		}
		else if (command->argument && command->argument->arguments && command->argument->arguments[0])
		{

			status = ft_command_path(command, table->env);
			if (g_global_state.is_dir)
			{
				ft_putstr_fd("Minishell: ", STDERR_FILENO);
				ft_panic_shell(command->argument->arguments[0], " Is a directory");
				exit(g_global_state.permission_status);
			}
			if (g_global_state.permission_status)
			{
				ft_panic_shell("minishell: ", strerror(g_global_state.permission_status));
				exit(g_global_state.permission_status);
			}
			if (!status)
				execve(command->argument->arguments[0], command->argument->arguments, env.table);
			else if (status != 126)
				ft_panic_shell(command->argument->arguments[0], ": command not found");
			exit(status);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (command->base.parent && command->base.parent->parent && command->base.parent->parent->token_type != ROOT)
			ft_restore_std_io(io);

	}
	return(0);
}

void ft_executor(t_symbol_table *table, t_container cont)
{
	t_vector	pipe_fd;
	size_t 		pipe_count;
	size_t		pipe_iter;
	int			status;


	status = 0;
	int isSignaled = 0;

	if (cont.exec_type == LIST)
	{
		pipe_count = 0;
		if (g_global_state.heredoc_signal == -1)
			status = ft_executor_with_list(cont.fd, cont.command, table);
		else
			status = 128 + g_global_state.heredoc_signal;
	}
	else
	{
		pipe_count = ft_pipe_count_tree(cont.tree->ast_node);
		pipe_fd = ft_open_pipe_fd(pipe_count);
		pipe_iter = 0;
		if (g_global_state.heredoc_signal == -1)
		{
			ft_execute_part(cont.fd, cont.tree->ast_node, table, &pipe_fd, &pipe_iter);
			
			for (size_t i = 0; i < pipe_fd.size; i++)
			{
				close(pipe_fd.arr[i]);
			}
			for (size_t i = 0; i < pipe_count + 1; i++)
			{
				wait(&status);
				if (!isSignaled)
				{
					if (WIFSIGNALED(status))
					{
						if (WTERMSIG(status) == SIGPIPE)
							status = WEXITSTATUS(status);
						else
							status = 128 + WTERMSIG(status);
						rl_catch_signals = 0;
						g_global_state.minishell_signal = SIGCHILD;
						ft_child_sigint(SIGNORMAL);
						isSignaled = 1;
					}
					else if (WIFEXITED(status))
						status = WEXITSTATUS(status);
				}
			}
		}
		else
			status = 128 + g_global_state.heredoc_signal;
		ft_free_tree(cont.tree->ast_node);	
		free(cont.tree);
	}
	g_global_state.heredoc_signal = -1;
	cont.exit_status = status;
	char* st_status = ft_itoa(cont.exit_status);
	ft_set_env(table->env, (t_hash_data){"?", st_status, HIDDEN});
	if (g_global_state.argument)
	{
		ft_set_env(table->env, (t_hash_data){"_", g_global_state.argument, VENV});
		free(g_global_state.argument);
		g_global_state.argument = NULL;
	}
	free(st_status);
	(void)pipe_count;
}
