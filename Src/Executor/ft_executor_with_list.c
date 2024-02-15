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
	
}

int ft_handle_external(t_io io, t_command* command, t_hash_table* env_table)
{
	(void)io;
	t_hash_table_arr env = ft_convert_env_to_args(env_table, 1);
	signal(SIGINT, SIG_IGN);
	int status = 0;
	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) 
	{
		rl_catch_signals = 0;
		signal(SIGINT, ft_child_sigint); 
		signal(SIGQUIT, SIG_DFL);

		ft_handle_redirect_ios(command->io);
		ft_command_fron_PATH(command, env_table);
		execve(command->argument->arguments[0], command->argument->arguments, env.table);
		
		ft_panic_shell(command->argument->arguments[0], ": command not found");
		// perror("execve: ");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			// signal(SIGINT, ctrl_c); 
			g_minishell_signal = SIGCHILD;
			if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
			{
				rl_catch_signals = 0;
				g_minishell_signal = SIGCHILD;
				ft_child_sigint(SIGNORMAL);
			}
			status = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
		{
			g_minishell_signal = SIGNORMAL;
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

	ft_expand_env(command, table);
	ft_init_arrey(&fd_vector, 0);
	ft_open_file(command, table->env, &fd_vector, io);
	t_function_callback biltin_func;
	if (!command->argument->arguments)
		biltin_func = NULL;
	else
		biltin_func =  ft_get_function(table->function, command->argument->arguments[0]);
	if (biltin_func)
	{
		ft_handle_redirect_ios(command->io);
		status = biltin_func(command, table);
		ft_restore_std_io(io);
		return status;
	}
	return ft_handle_external(io, command, table->env);
}