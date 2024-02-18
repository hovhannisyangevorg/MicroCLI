/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:04:57 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 21:59:44 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_ignore_quots(char *str, char quot, size_t i)
{
	if (str && str[i])
	{
		++i;
		while (str[i] && str[i] != quot)
			++i;
	}
	return (i);
}

char	*ft_tokenize_with_delims(char *str, char *delim, int *type)
{
	int			i;
	int			is_one_sym;
	char		*token_start;
	static char	*next_token;

	if (str)
		next_token = str;
	if (!next_token)
		return (NULL);
	token_start = next_token;
	i = 0;
	is_one_sym = 0;
	*type = MNNULL;
	if (token_start[i] == '\"' || token_start[i] == '\'')
	{
		*type = MTEXT;
		i = ft_ignore_quots(token_start, token_start[i], 0);
	}
	while (token_start[i])
	{
		if (ft_strchr(delim, token_start[i])) 
		{
			if (token_start[i] && token_start[i + 1] && \
					token_start[i] == token_start[i + 1] && \
					!ft_is_breckets(ft_get_type_map(token_start[i])))
			{
				is_one_sym = 0;
				*type = -token_start[i];
			}
			else
			{
				is_one_sym = 1;
				*type = token_start[i];
			}
			token_start[i] = '\0';
			if (!is_one_sym)
				++i;
			next_token = token_start + i + 1;
			return (token_start);
		}
		else
			*type = MTEXT;
		++i;
	}
	next_token = NULL;
	return (token_start);
}

char	*ft_tokenize_with_space(char *expr, int *type)
{
	int				i;
	char			*token_start;
	static char		*next_token;

	if (expr)
		next_token = expr;
	if (!next_token)
		return (NULL);
	i = 0;
	*type = NNULL;
	token_start = next_token;
	if (token_start[i] == '\"' || token_start[i] == '\'')
	{
		*type = MTEXT;
		i = ft_ignore_quots(token_start, token_start[i], 0);
	}
	while (token_start[i])
	{
		if (ft_isspace(token_start[i]))
		{
			*type = MTEXT;
			token_start[i] = '\0';
			++i;
			while (token_start[i] && ft_isspace(token_start[i]))
				++i;
			if (!token_start[i])
				next_token = NULL;
			else
				next_token = token_start + i;
			return (token_start);
		}
		++i;
	}
	next_token = NULL;
	return (token_start);
}

t_list_token	*ft_tokenize_string_space(char *input)
{
	int				type;
	char			*token;
	t_list_token	*list;

	type = 0;
	list = ft_init_list();
	token = ft_tokenize_with_space(input, &type);
	while (token != NULL)
	{
		ft_push_back(list, type, token);
		token = ft_tokenize_with_space(NULL, &type);
	}
	return (list);
}

t_list_token	*ft_tokenize(char *input, char *delims)
{
	t_list_token	*list;
	t_list_token	*space_list;
	t_token			*tmp;
	t_token			*head;
	char			*token;
	char			*tmp_token;
	int				type;

	type = 0;
	list = ft_init_list();
	space_list = ft_tokenize_string_space(input);
	head = space_list->head;
	while (head)
	{
		tmp = head->next;
		token = ft_tokenize_with_delims(head->token, delims, &type);
		while (token)
		{
			if (type != MTEXT && type)
			{
				if (*token)
					ft_push_back(list, TEXT, token);
				tmp_token = ft_get_type(ft_get_type_map(type));
				ft_push_back(list, ft_get_type_map(type), tmp_token);
				free(tmp_token);
			}
			else if (type)
				ft_push_back(list, ft_get_type_map(type), token);
			token = ft_tokenize_with_delims(NULL, delims, &type);
		}
		free(head->token);
		free(head);
		head = tmp;
	}
	free(space_list);
	return (list);
}
