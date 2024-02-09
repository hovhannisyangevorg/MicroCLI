/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_with_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:54:14 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/08 23:19:38 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_restore_std_io(t_io io)
{
	dup2(io.input, STDIN_FILENO);
	dup2(io.output, STDOUT_FILENO);
	dup2(io.error, STDERR_FILENO);
}

t_io ft_init_io_restore(t_io io)
{
	t_io io_res;

	io_res.input	= dup(io.input);
	io_res.output	= dup(io.output);
	io_res.error	= dup(io.error);
	return io_res;
}

void	ft_open_file(t_command *command, t_hash_table *env, t_vector* fd_vector)
{
	t_ast_node* node;

	node		= ft_redirect_to_ast_node(command->redirect);
	while (node)
	{
		ft_open_type(ft_ast_to_redirect(node), command, fd_vector, env);
		node = node->left;
	}
	ft_close_fd(fd_vector);
}

int ft_handle_external(t_io io, t_command* command, t_hash_table* env_table)
{
	(void)io;
	t_hash_table_arr env = ft_convert_env_to_args(env_table);
	int status = 0;
	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) 
	{
		ft_handle_redirect_ios(command->io);
		// printf("pid: %s\n", ft_get_env(env_table, "$"));
		ft_command_fron_PATH(command, env_table);
		// printf("exec: %s\n", command->argument->arguments[0]);
		execve(command->argument->arguments[0], command->argument->arguments, env.table);
			
		ft_panic_shell(command->argument->arguments[0], ": command not found");
		// perror("execve: ");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return(status);
}

int	ft_executor_with_list(t_io io, t_command *command, t_hash_table* env, t_hash_table* function_table)
{
	(void)function_table;
	int			status;
	// char		*st_str;
	t_vector	fd_vector;


	ft_init_arrey(&fd_vector, 0);
	ft_open_file(command, env, &fd_vector);
	t_function_callback biltin_func =  ft_get_function(function_table, command->argument->arguments[0]);
	if (biltin_func)
	{
		// printf("%d\n", io.output);
		// t_io io_res = ft_init_io_restore(io);

		// int f = dup(STDOUT_FILENO);
		// // int f = dup(io.input);
		// // ft_restore_std_io(io_res);
		// // ft_init_io_std()
		ft_handle_redirect_ios(command->io);
		// close(command->io.input);
		// close(command->io.output);
		// close(command->io.error);
		status = biltin_func(command, env);
		// dup2(f, STDOUT_FILENO);
		ft_restore_std_io(io);
		return status;
	// 	// status = biltin_func(command, env);
	// 	// st_str = ft_itoa(status);
	// 	// ft_set_env(env, "?", st_str, 1);
	// 	// free(st_str);
	}
	// status 		= ft_handle_external(command, env);
	return ft_handle_external(io, command, env);
	// st_str 		= ft_itoa(status);
	// ft_set_env(env, "?", st_str, 1);
	// free(st_str);
}