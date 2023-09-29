/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthes_balancer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:55:10 by gevorg            #+#    #+#             */
/*   Updated: 2023/09/27 16:09:30 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parenthes_balancer(char *expression)
{
	int i;
	int balanced;
	
	t_stack *stack;
	stack = ft_initialize_stack();
	i = 0;
	while (expression && expression[i])
	{
		if (expression[i] == '(')
			ft_push_stack(stack, '(');
		else if (expression[i] == ')')
		{
			if (ft_pop_stack(stack) != '(')
			{
				ft_free_stack(stack);
				free(stack);
				return (0);
			}
		}
		i++;
	}
	balanced = ft_is_empty(stack);
	ft_free_stack(stack);
	free(stack);
	return (balanced);
}


void ft_is_balanc(char *expression)
{
	if (!ft_parenthes_balancer(expression))
		ft_panic("MiniShell Oops: Syntax error parentheses are not balanced !   `('");
}
