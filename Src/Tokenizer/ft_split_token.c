/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:15:33 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 21:38:51 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	ft_lensep(char *str, char *delims)
{
	size_t	i;

	i = 0;
	while (str && str[i] && ft_strchr(delims, str[i]))
		i++;
	return (i);
}

static size_t	ft_lenminitok(char *str, size_t index)
{
	size_t	i;
	size_t	size;

	i = index;
	size = 0;
	while (str && str[i++])
		size++;
	return (size);
}

static void	ft_splitted(t_token *token, char *delims)
{
	t_token	*new;
	size_t	pipe_size;
	size_t	text_size;
	char	*expr;
	char	*str_tmp;

	expr = token->token;
	pipe_size = ft_lensep(expr, delims);
	text_size = ft_lenminitok(expr, pipe_size);
	if (pipe_size <= 0)
		return ;
	if (pipe_size > 0 && text_size == 0)
	{
		token->type = *(expr + pipe_size - 1);
		free(token->token);
		token->token = ft_strdup("NULL");
		return ;
	}
	new = (t_token *)malloc(sizeof(t_token));
	new->type = *(expr + pipe_size - 1);
	ft_init_token(new, expr[pipe_size - 1], ft_strdup("NULL"));
	if (token->prev)
	{
		new->prev = token->prev;
		new->next = token;
		token->prev->next = new;
		token->prev = new;
	}
	str_tmp = ft_strdup(expr + pipe_size);
	free(token->token);
	token->token = str_tmp;
}

void	ft_split_token(t_list_token *list)
{
	t_token	*token;

	token = list->head;
	while (token)
	{
		if (token->type == TEXT)
			ft_splitted (token, OPERATORS);
		token = token->next;
	}
}
