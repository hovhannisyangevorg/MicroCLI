/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_balanced.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:55:10 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/20 18:05:18 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_is_quota_balanc(char *input)
{
	int i;
	int single_quotes;
	int double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	if (input == NULL)
		return 0;

    while (input && input[i])
	{
        if (input[i] == '\'')
		{
			single_quotes++;
			i = ft_ignore_quots(input, input[i], i);
			continue ;
        } else if (input[i] == '\"')
		{
			double_quotes++;
			i = ft_ignore_quots(input, input[i], i);
			continue ;
		}
		i++;
    }
    return ((single_quotes % 2 == 0) && (double_quotes % 2 == 0));
}

static int	ft_is_balanc(char *line)
{
	int i;
	int balanced;
	t_stack *stack;
	
	stack = ft_initialize_stack();
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '(')
			ft_push_stack(stack, '(');
		else if (line[i] == ')')
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

void ft_balanced(char *line)
{
	char *color;

	if (!ft_is_balanc(line))
	{
		color = RED "Bash Oops! : " BLACK "Syntax error parentheses are not balanced ! `('";
		ft_panic(color);
	}else if (!ft_is_quota_balanc(line))
	{
		color = RED "Bash Oops! : " BLACK "Syntax error quotes are not balanced ! `\" or `\''";
		ft_panic(color);
	}
}
