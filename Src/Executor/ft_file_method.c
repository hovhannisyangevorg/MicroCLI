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

void	ft_open_file(t_process_info *info, t_vector* fd_vector)
{
	t_ast_node* node;

	node		= ft_redirect_to_ast_node(info->command->redirect);
	while (node)
	{
		if (g_global_state.heredoc_signal != -1)
			break;
		ft_open_type(ft_ast_to_redirect(node), info, fd_vector);
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

void	ft_open_all_fd(t_ast_node *ast_node, t_process_info *info)
{
	t_vector fd_vector;
	if (!ast_node)
		return ;
	ft_init_arrey(&fd_vector, 0);
	if (ast_node->token_type == COMMAND)
	{
		info->command = ft_ast_to_command(ast_node);
		ft_open_file(info, &fd_vector);
	}
	ft_open_all_fd(ast_node->left, info);
	ft_open_all_fd(ast_node->right, info);
}

void ft_close_fd(t_vector *fd_vector)
{
	size_t i;

	i = 0;
	while (i < fd_vector->size)
		close(fd_vector->arr[i++]);
	free(fd_vector->arr);
}

int ft_open_file_type_mode(t_redirect *redirect, t_process_info *info, t_vector *fd_vector, t_file_mode modes)
{
	int fd;

	fd = -1;
	if (redirect->base.token_type == modes.mode)
	{
		if (modes.is_heredoc)
			fd = open_heredoc(redirect, info->table->env);
		else
		{
			fd = open(redirect->argument, modes.open_mode, 0664);
			if (access(redirect->argument, modes.access_mode) == -1)
			{
				g_global_state.permission_status = errno;
				close(fd);
				fd = -1;
				return fd;
			}
		}
		if (modes.is_input && info->command->io.input < fd)
			info->command->io.input = fd;
		else if (!modes.is_input && info->command->io.output < fd)
			info->command->io.output = fd;
		else
			ft_push_arrey(fd_vector, fd);
	}
	return fd;
}

t_file_mode ft_init_mode(t_token_type type)
{
	t_file_mode mode;

	if (type == WRITE)
		mode = (t_file_mode){.is_heredoc = 0, .is_input = 0, .access_mode = W_OK, .mode = WRITE, .open_mode = O_TRUNC | O_WRONLY | O_CREAT};
	else if (type == READ)
		mode = (t_file_mode){.is_heredoc = 0, .is_input = 1, .access_mode = R_OK, .mode = READ, .open_mode = O_RDONLY};
	else if (type == APPEND)
		mode = (t_file_mode){.is_heredoc = 0, .is_input = 0, .access_mode = R_OK | W_OK, .mode = APPEND, .open_mode = O_APPEND | O_WRONLY | O_CREAT};
	else if (type == HEREDOC)
		mode = (t_file_mode){.is_heredoc = 1, .is_input = 1, .mode = HEREDOC};
	else
		mode = (t_file_mode){0, 0, 0, 0, 0};
	return mode;
}


void	ft_open_type(t_redirect *redirect, t_process_info *info, t_vector *fd_vector)
{
	int 		fd;
	t_file_mode	mode;

	fd = -1;
	
	if (g_global_state.permission_status == SUCCESS_CODE)
	{
		mode = ft_init_mode(redirect->base.token_type);
		fd = ft_open_file_type_mode(redirect, info, fd_vector, mode);
		if (fd < 0)
			return ;
	}
}
