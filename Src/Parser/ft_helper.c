/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:55:56 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/24 21:07:13 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_should_ast_create(t_list_token *list)
{
	size_t	pc;
	t_token	*temp;
	int is_pipe;

	pc = 0;
	is_pipe = 0;
	temp = list->head;
	while (temp)
	{
		char* tok = temp->token;
		while(*tok)
		{
			if (*tok == '|' || *tok == '&')
			{
				is_pipe = 1;
				break;
			}		
			++tok;
		}
		if(temp->type == PIPE || temp->type == AND || is_pipe)
			pc++;
		temp = temp->next;
	}
	return (pc != 0);
}


int ft_should_ast_created(t_list_token *list)
{
	size_t	pc;
	t_token	*temp;

	pc = 0;
	temp = list->head;
	while (temp)
	{
		if (temp->type == PIPE || temp->type == AND || temp->type == OPBREK || temp->type == CLBREK || temp->type == JOB)
			pc++;
		temp = temp->next;
	}
	return (pc != 0);
}