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

void ft_handle_external_command(t_command* command, t_symbol_table* table, char** env)
{
	int status;

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
		execve(command->argument->arguments[0], command->argument->arguments, env);
	else if (status != 126)
		ft_panic_shell(command->argument->arguments[0], ": command not found");
	exit(status);
}


void ft_handle_child_process(t_process_info *info, int is_pipe)
{
	t_function_callback		biltin_func;
	t_vector				fd_vector;

	biltin_func = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	g_global_state.permission_status = 0;
	ft_init_arrey(&fd_vector, 0);
	ft_open_file(info, &fd_vector);
	ft_handle_redirect_ios(info->command->io);
	if (is_pipe)
	{
		ft_hendle_pipe(&info->pipe_fd, info->pipe_iter, info->command->io);
		if (!info->command->argument->arguments)
			biltin_func = NULL;
		else
			biltin_func = ft_get_function(info->table->function, info->command->argument->arguments[0]);
		if (biltin_func)
			exit(biltin_func(info->command, info->table));
	}
	if (!biltin_func && info->command->argument && info->command->argument->arguments && info->command->argument->arguments[0])
		ft_handle_external_command(info->command, info->table, info->env.table);
	exit(EXIT_SUCCESS);
}

int		ft_execute_command(t_process_info *info)
{
	int		status;

	status = EXIT_SUCCESS;
	g_global_state.is_dir = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);
	signal(SIGINT, SIG_IGN);
	g_global_state.permission_status = SUCCESS_CODE;
	info->env = ft_convert_env_to_args(info->table->env, 1, 0);
	ft_expand_env(info->command, info->table);

	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) 
		ft_handle_child_process(info, 1);
	else if (info->command->base.parent && info->command->base.parent->parent && info->command->base.parent->parent->token_type != ROOT)
			ft_restore_std_io(info->io);
	return(status);
}

int ft_get_signal_exit(int status, int *is_signaled)
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
		*is_signaled = 1;
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int ft_get_exit_status(size_t pipe_count)
{
	int		status;
	size_t	i;
	int		is_signaled;
	
	is_signaled = 0;
	i = 0;
	status = EXIT_SUCCESS;
	while (i < pipe_count + 1)
	{
		wait(&status);
		if (!is_signaled)
			status = ft_get_signal_exit(status, &is_signaled);
		++i;
	}
	return status;
}

void ft_update_env_exit(t_container cont, t_symbol_table* table)
{
	char* status;
	
	status = ft_itoa(cont.exit_status);
	ft_set_env(table->env, (t_hash_data){"?", status, HIDDEN});
	if (g_global_state.argument)
	{
		ft_set_env(table->env, (t_hash_data){"_", g_global_state.argument, VENV});
		free(g_global_state.argument);
		g_global_state.argument = NULL;
	}
	free(status);
}

void ft_dispatch_container(t_container cont, t_process_info* info)
{
	info->pipe_iter = 0;
	info->io = cont.fd;
	info->table = cont.table;
	if (cont.exec_type == LIST)
	{
		ft_init_arrey(&info->pipe_fd, 0);
		info->pipe_count = 0;
		info->status = ft_executor_with_list(cont.fd, cont.command, info->table);
	}
	else
	{
		info->pipe_count = ft_pipe_count_tree(cont.tree->ast_node);
		info->pipe_fd = ft_open_pipe_fd(info->pipe_count);
		ft_execute_part(cont.tree->ast_node, info, &info->pipe_iter);
			
		ft_free_tree(cont.tree->ast_node);	
		free(cont.tree);
	}
}

void ft_executor(t_symbol_table *table, t_container cont)
{
	int				status;
	t_process_info	info;
	size_t			i;


	status = EXIT_SUCCESS;
	i = 0;
	if (g_global_state.heredoc_signal == -1)
	{
		ft_dispatch_container(cont, &info);
		while (i < info.pipe_fd.size)
		{
			close(info.pipe_fd.arr[i]);
			++i;
		}
		status = ft_get_exit_status(info.pipe_count);
	}
	else
		status = 128 + g_global_state.heredoc_signal;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);
	g_global_state.heredoc_signal = -1;
	cont.exit_status = status;
	ft_update_env_exit(cont, table);
}
