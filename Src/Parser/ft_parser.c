/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:56:54 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/08 22:15:13 by gevorg           ###   ########.fr       */
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
	t_container 	container;

	container 		= ft_sematic(list);
	container.fd	= ft_init_io();
	return (container);
}