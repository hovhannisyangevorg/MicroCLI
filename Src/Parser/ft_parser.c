/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:56:54 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/16 22:15:09 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_io	ft_init_io()
{
	t_io io;

	io.input	= -1;
	io.output	= -1;
	io.error	= -1;
	return (io);
}

void	ft_init_io_fd(t_io *io, t_io_type io_type, int fd)
{
	if (io_type == STDIN)
		io->input = dup(fd);
	else if (io_type == STDOUT)
		io->output = dup(fd);
	else if (io_type == STDERR)
		io->error = dup(fd);
}

t_container ft_parser(t_list_token *list)
{
	ft_print_list(list->head);
	int 			is_ast;
	t_container 	container;
	t_global_tree	*tree;

	is_ast 	= ft_should_ast_created(list);
	if (is_ast)
	{
		tree 	= ft_sematic(list, is_ast);
		container.exec_type = TREE;
		container.tree = tree;
	}
	else
	{
		container.exec_type = LIST;
		container.list = list;
	}
	container.fd = ft_init_io();
	return (container);
}