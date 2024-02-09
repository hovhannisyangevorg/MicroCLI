/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_panic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:06:27 by gehovhan          #+#    #+#             */
/*   Updated: 2024/02/08 22:14:16 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_panic(char *error)
{
	write (2, error, ft_strlen(error));
	write (2, "\n", 1);
	exit (1);
}

void	ft_panic_shell(char *error, char *current)
{
	if (error)
		write (2, error, ft_strlen(error));
	if (current)
		write (2, current, ft_strlen(current));
	write(2, "\n", 1);
}

