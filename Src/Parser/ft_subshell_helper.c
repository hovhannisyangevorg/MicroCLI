/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 03:25:43 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/19 03:25:53 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_remove_command_redirect(t_list_token *list)
{
	while (list->head && ft_iscommand(list->head->type))
	{
		if (ft_is_breckets(list->head->type))
			ft_remove_subshell(list);
		else
			ft_pop_front(list);
	}
}
