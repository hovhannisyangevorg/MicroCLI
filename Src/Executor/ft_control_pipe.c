/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:58:30 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 18:40:54 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_hendle_pipe(t_vector * pipe_fd, size_t pipe_iter, t_io io)
{
	size_t i;

	i = 0;
	if (pipe_iter != 0 && io.input == STDIN_FILENO)
		dup2(pipe_fd->arr[(pipe_iter - 1) * 2], STDIN_FILENO);
	if (pipe_iter != pipe_fd->size / 2 && io.output == STDOUT_FILENO)
		dup2(pipe_fd->arr[(pipe_iter * 2) + 1], STDOUT_FILENO);
	while (i < pipe_fd->size)
		close(pipe_fd->arr[i++]);
}

void ft_handle_redirect_ios(t_io io)
{
	if (io.input != STDIN_FILENO)
	{
		dup2(io.input, STDIN_FILENO);
		close(io.input);
	}
	if (io.output != STDOUT_FILENO)
	{
		dup2(io.output, STDOUT_FILENO);
		close(io.output);
	}
	if (io.error != STDERR_FILENO)
	{
		dup2(io.error, STDERR_FILENO);
		close(io.error);
	}
}

char	*ft_get_last_arg(t_command* command)
{
	if (!command || !command->argument || !command->argument->arguments || !command->argument->arguments[0])
		return NULL;
	size_t i = 0;
	while (command->argument->arguments[i])
		++i;
	return ft_strdup(command->argument->arguments[i - 1]);
}

int		ft_open_process_for_pipe(t_io io, t_ast_node *tree, t_symbol_table* table, t_vector *pipe_fd, size_t* pipe_iter)
{
	t_ast_node *ast_node;


	if (*pipe_iter <= pipe_fd->size / 2)
	{
		ast_node = ft_ast_left_most(tree->left);
		if (ast_node)
		{

			ft_execut_command(io, ft_ast_to_command(ast_node), table, pipe_fd, *pipe_iter);
			g_global_state.argument = ft_get_last_arg(ft_ast_to_command(ast_node));
			(*pipe_iter)++;
		}
		ft_execut_command(io, ft_ast_to_command(tree->right), table, pipe_fd, *pipe_iter);
		g_global_state.argument = ft_get_last_arg(ft_ast_to_command(tree->right));
		(*pipe_iter)++;
	}
	
	return (0);
}	


void	ft_execute_part(t_io io, t_ast_node *tree, t_symbol_table* table, t_vector *pipe_fd, size_t* pipe_iter)
{
	if (!tree)
		return ;
	ft_execute_part(io, tree->left, table, pipe_fd, pipe_iter);
	
	if (tree->token_type == PIPE)
	{
		ft_open_process_for_pipe(io, tree, table, pipe_fd, pipe_iter);
		return ;
	}
	ft_execute_part(io, tree->right, table, pipe_fd, pipe_iter);
}