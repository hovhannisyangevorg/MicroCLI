/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:48:39 by gevorg            #+#    #+#             */
/*   Updated: 2023/10/01 13:04:12 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

static int ft_hash(int num)
{
    return (num * (-1));
}

char	*ft_create_token(const char *str, int token_start, int token_length)
{
	int i;
	int j;
	char *token;

	token = (char *)malloc((token_length + 1) * sizeof(char));
	if (!token)
		return(NULL);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (i >= token_start && j< token_length)
		{
			token[j] = str[i];
			j++;
		}
		++i;
	}
	token[j] = '\0';
	return (token);
}

int ft_ignor_quot(char *str, char quot, size_t i)
{
	if (str && str[i])
	{
		i++;
		while (str[i] && str[i] != quot)
			i++;
		if (str && str[i] && str[i] == quot)
			i++;
	}
	return (i);
}

static int	ft_find_index(char *expr, int index)
{
	int i;
	int res;
	
	t_stack *stack;
	stack = ft_initialize_stack();
	i = 0;
	while (expr && expr[i])
	{
		if (expr[i] == '(')
		{
			ft_push_stack(stack, i);
		}
		else if (expr[i] == ')')
		{
			if (stack->top)
			{
				res = stack->top->data;
				if (res == index)
					return i;
			}
			ft_pop_stack(stack);
		}
		++i;
	}
	ft_free_stack(stack);
	free(stack);
	return (-1);
}

// void tokenize(char* str, char* delims)
// {

// }

t_list_token *ft_multi_split(char *str, char *delims, int issub)
{
	size_t			i;
	t_list_token	*list;
	char 			*tmp;
	int 			token_start;
	int 			token_length;
	

	list = ft_init_list();
	i = -1;
	int j = 0;
	token_start = 0;

	while (++i <= ft_strlen(str))
	{
		if (str[i] && ft_strchr("\"\'", str[i]))
			i = ft_ignor_quot(str, str[i], i);
		if (str[i] == '(' && !issub)
		{
			j = ft_find_index(str, i);
			if ( j != -1 )
				i = j + 1;
		}
		if (ft_strchr(delims, str[i]) || !str[i])
		{
			token_length = i - token_start;
			tmp = ft_create_token(str, token_start, token_length);
			if (!tmp)
				return (NULL);
			if (str[i] && str[i + 1] && (str[i + 1] == str[i]))
			{
				ft_push_back(list, ft_hash(str[i]), tmp);
				i += 2;
			}
			else
			{
				ft_push_back(list,  str[i], tmp);
				while (str[i] && ft_strchr(delims, str[i]))
					i++;	
			}
			free(tmp);
			if (str[i])
				token_start = i;
		}
	}
	return (list);
}