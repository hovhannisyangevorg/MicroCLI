/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_balanced.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:55:10 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 19:47:11 by gevorg           ###   ########.fr       */
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
		return 1;

    while (input && input[i])
	{
        if (input[i] == '\'')
		{
			single_quotes++;
			i = ft_ignore_quots(input, input[i], i);
			if (input[i])
			{
				if (input[i] == '\'')
					++single_quotes;
				++i;
			}
			continue ;
        } else if (input[i] == '\"')
		{
			double_quotes++;
			i = ft_ignore_quots(input, input[i], i);
			if (input[i])
			{
				if (input[i] == '\"')
					++double_quotes;
				++i;
			}
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

int ft_balanced(char *line)
{
	if (!ft_is_balanc(line))
	{
		ft_panic_shell("minishell: ", "unexpected EOF while looking for matching `('");
		return (2);
	}
	else if (!ft_is_quota_balanc(line))
	{
		ft_panic_shell("minishell: ", "unexpected EOF while looking for matching `\'\'");
		return (2);
	}
	return EXIT_SUCCESS;
}
