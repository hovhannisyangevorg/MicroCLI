/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_method.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:15:25 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 18:51:06 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

t_vector	ft_open_pipe_fd(size_t pipe_count)
{
	size_t		i;
	size_t		j;
	t_vector	pipe_fd;

	i = -1;
	j = 0;
	ft_init_arrey(&pipe_fd, ((pipe_count) * 2));

	while (++i < pipe_count)
	{
		pipe(pipe_fd.arr + j);
		j += 2;
	}
	return (pipe_fd);
}

void	ft_open_all_fd(t_ast_node *ast_node, t_hash_table *env, t_io io)
{
	t_vector fd_vector;
	if (!ast_node)
		return ;
	ft_init_arrey(&fd_vector, 0);
	if (ast_node->token_type == COMMAND)
		ft_open_file(ft_ast_to_command(ast_node), env, &fd_vector, io);
	ft_open_all_fd(ast_node->left, env, io);
	ft_open_all_fd(ast_node->right, env, io);
}

void ft_close_fd(t_vector *fd_vector)
{
	size_t i;

	i = 0;
	while (i < fd_vector->size)
		close(fd_vector->arr[i++]);
	free(fd_vector->arr);
}


void	ft_open_type(t_redirect *redirect, t_command *cmd, t_vector *fd_vector, t_hash_table *env, t_io io)
{
	int fd;

	fd = -1;
	
	if (g_global_state.permission_status == SUCCESS_CODE)
	{
		if (redirect->base.token_type == WRITE)
		{
			fd = open(redirect->argument, O_TRUNC | O_WRONLY | O_CREAT, 0664);
			if (access(redirect->argument, W_OK) == -1)
			{
				g_global_state.permission_status = errno;
				close(fd);
				return;
			}
			else if (cmd->io.output < fd)
				cmd->io.output = fd;
			else
				ft_push_arrey(fd_vector, fd);
		}
		else if (redirect->base.token_type == READ)
		{
			fd = open(redirect->argument,  O_RDONLY);
			if (access(redirect->argument, R_OK) == -1)
			{
				g_global_state.permission_status = errno;
				close(fd);
				return;
			}
			else if (cmd->io.input < fd)
				cmd->io.input = fd;
			else
				ft_push_arrey(fd_vector, fd);
		}
		else if (redirect->base.token_type == APPEND)
		{
			fd = open(redirect->argument, O_APPEND | O_WRONLY | O_CREAT, 0664);
			if (access(redirect->argument, R_OK | W_OK) == -1)
			{
				g_global_state.permission_status = errno;
				close(fd);
				return;
			}
			else if (cmd->io.output < fd)
				cmd->io.output = fd;
			else
				ft_push_arrey(fd_vector, fd);
		}
		else if (redirect->base.token_type == HEREDOC)
		{
			fd = open_heredoc(redirect, env, io);
			if (cmd->io.input < fd)
				cmd->io.input = fd;
			else
				ft_push_arrey(fd_vector, fd);
		}
	}
}
