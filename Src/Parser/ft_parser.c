/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:56:54 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/01 18:45:11 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_io	ft_init_io()
{
	t_io io;

	io.input	= 0;
	io.output	= 1;
	io.error	= 2;
	return (io);
}

// void	ft_init_io_fd(t_io *io, t_io_type io_type, int fd)
// {
// 	if (io_type == STDIN)
// 		io->input = dup(fd);
// 	else if (io_type == STDOUT)
// 		io->output = dup(fd);
// 	else if (io_type == STDERR)
// 		io->error = dup(fd);
// }

t_container ft_parser(t_list_token *list)
{
	ft_print_list(list->head);
	int 			is_ast;
	t_container 	container;

	t_global_tree	*tree;

	is_ast 	= ft_should_ast_created(list);
	tree = NULL;
	if (is_ast)
	{
		tree 	= ft_sematic(list, is_ast);
		container.exec_type = TREE;
		container.tree = tree;
		// char *leak = ft_strdup("");
		// ft_ast_print(tree->ast_node, leak, 0, 1);
		// free(leak);
		// ft_free_tree(tree->ast_node);
		// container.tree = NULL;
	}
	else
	{
		container.exec_type = LIST;
		container.list = list;
	}
	container.fd = ft_init_io();
	return (container);
}