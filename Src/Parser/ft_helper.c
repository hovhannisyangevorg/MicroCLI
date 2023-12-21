/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:55:56 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/18 13:02:01 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_should_ast_create(t_list_token *list)
{
	size_t	pc;
	t_token	*temp;

	pc = 0;
	temp = list->head;
	while (temp)
	{
		if(temp->type == PIPE || temp->type == AND)
			pc++;
		temp = temp->next;
	}
	return (pc != 0);
}