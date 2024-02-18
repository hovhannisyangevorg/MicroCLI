/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_with_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:54:14 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/14 22:58:44 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_restore_std_io(t_io io)
{
	dup2(io.input, STDIN_FILENO);
	close(io.input);
	dup2(io.output, STDOUT_FILENO);
	close(io.output);
	dup2(io.error, STDERR_FILENO);
	close(io.error);
}

t_io ft_init_io_restore(t_io io)
{
	t_io io_res;

	io_res.input	= dup(io.input);
	io_res.output	= dup(io.output);
	io_res.error	= dup(io.error);
	return io_res;
}

void	ft_open_file(t_command *command, t_hash_table *env, t_vector* fd_vector, t_io io)
{
	t_ast_node* node;

	node		= ft_redirect_to_ast_node(command->redirect);
	while (node)
	{
		if (g_global_state.heredoc_signal != -1)
			break;
		ft_open_type(ft_ast_to_redirect(node), command, fd_vector, env, io);
		node = node->left;
	}
	ft_close_fd(fd_vector);
}

void ft_child_sigint(int num)
{
	(void)num;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);

}


int ft_handle_external(t_io io, t_command* command, t_hash_table* env_table)
{
	t_hash_table_arr env = ft_convert_env_to_args(env_table, 1, 0);
	t_vector fd_vector;
	g_global_state.permission_status = SUCCESS_CODE;
	signal(SIGINT, SIG_IGN);
	int status = 0;
	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) 
	{
		rl_catch_signals = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_init_arrey(&fd_vector, 0);
		ft_open_file(command, env_table, &fd_vector, io);
		ft_handle_redirect_ios(command->io);
		if (g_global_state.permission_status)
		{
			ft_panic_shell("minishell: ", strerror(g_global_state.permission_status));
			exit(g_global_state.permission_status);
		}
		if (command->argument && command->argument->arguments && command->argument->arguments[0])
		{
			status = ft_command_fron_PATH(command, env_table);
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
		exit(status);
	}
	else
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			g_global_state.minishell_signal = SIGCHILD;
			if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
			{
				rl_catch_signals = 0;
				g_global_state.minishell_signal = SIGCHILD;
				ft_child_sigint(SIGNORMAL);
			}
			status = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
		{
			g_global_state.minishell_signal = SIGNORMAL;
			status = WEXITSTATUS(status);
		}
		signal(SIGINT, sigint_handler); 
		ft_restore_std_io(io);
	}
	return(status);
}

void ft_expand_env(t_command *command, t_symbol_table* table);
int	ft_executor_with_list(t_io io, t_command *command, t_symbol_table* table)
{
	int			status;
	t_vector	fd_vector;
	t_function_callback biltin_func;

	g_global_state.argument = ft_get_last_arg(command);
	g_global_state.permission_status = SUCCESS_CODE;
	ft_expand_env(command, table);
	g_global_state.is_dir = 0;

	
	if (!command->argument->arguments)
		biltin_func = NULL;
	else
		biltin_func =  ft_get_function(table->function, command->argument->arguments[0]);
	if (biltin_func)
	{
		ft_init_arrey(&fd_vector, 0);

		ft_open_file(command, table->env, &fd_vector, io);
		if (g_global_state.permission_status != SUCCESS_CODE)
		{
			ft_panic_shell("minishell: ", strerror(g_global_state.permission_status));
			return g_global_state.permission_status;
		}
		ft_handle_redirect_ios(command->io);
		status = biltin_func(command, table);
		ft_restore_std_io(io);
		return status;
	}
	return ft_handle_external(io, command, table->env);
}