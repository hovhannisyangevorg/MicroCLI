/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shanting_stack_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 04:02:48 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/19 04:04:29 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_print_shat_steak(t_global_stack *stack)
{
	t_shant_stack	*tmp;

	tmp = stack->top;
	while (tmp)
	{
		printf("shating token =>%s\n", tmp->ast_node->token);
		tmp = tmp->next;
	}
}
