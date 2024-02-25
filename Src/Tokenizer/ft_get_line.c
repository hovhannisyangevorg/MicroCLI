/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:05:13 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 20:47:27 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_line(void)
{
	char	*line;

	line = readline("minishell $> ");
	if (line)
	{
		add_history(line);
		ft_push_history(&g_global_state.history, line);
	}
	return (line);
}
