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

#include "minishell.h"

int		ft_count_token(char *str, char *delims, int str_len)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < str_len)
	{
        if (ft_strchr(delims, str[i])) 
		{
			count++;
			while (str[i] && ft_strchr(delims, str[i]))
				i++;
		} else
			i++;
	}
	if (str_len && !ft_strchr(delims, str[str_len - 1]))
		count++;
	return (count);
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

char **ft_multi_split(char *str, char *delims)
{
	int		i;
	int		str_len;
	char	**tokens;
	int		tokens_count;
	int		token_index;
	int 	token_start;
	int 	token_length;
	
	str_len 		= ft_strlen(str);
	tokens_count 	= ft_count_token(str, delims, str_len);
	tokens			= (char **)malloc((tokens_count + 1) * sizeof(char *));
	if (!tokens)
		return (0);

	i = 0;
	token_index = 0;
	token_start = 0;
	while (i <= str_len)
	{
		if (ft_strchr(delims, str[i]) || !str[i])
		{
			token_length = i - token_start;
			tokens[token_index] = ft_create_token(str, token_start, token_length);
			if (!tokens[token_index])
			{
				ft_vecstrdel(&tokens);
				return (NULL);
			}
			token_index++;
			while (str[i] && ft_strchr(delims, str[i]))
				i++;
			if (str[i])
			token_start = i;
		}
		i++;
	}
	tokens[tokens_count] = NULL;
	return (tokens);
}
