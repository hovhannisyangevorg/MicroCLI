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

t_io	ft_init_io_std()
{
	t_io io;

	io.error	= dup(STDERR_FILENO);
	io.input	= dup(STDIN_FILENO);
	io.output	= dup(STDOUT_FILENO);
	return io;
}

t_container ft_parser(t_list_token *list)
{
	t_container 	container;

	container 		= ft_sematic(list);
	container.fd	= ft_init_io_std();
	return (container);
}