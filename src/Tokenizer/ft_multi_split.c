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



t_token *ft_multi_split(char *str, char *delims)
{
	size_t	i;
	t_token *head;
	char 	*tmp;
	int 	token_start;
	int 	token_length;
	
	ft_init_list(&head);
	i = -1;
	token_start = 0;
	while (++i <= ft_strlen(str))
	{
		if (ft_strchr(delims, str[i]) || !str[i])
		{
			token_length = i - token_start;
			tmp = ft_create_token(str, token_start, token_length);
			if (!tmp)
				return (NULL);
			if (str[i] && str[i + 1] && (str[i + 1] == str[i]))
				ft_push_back(&head, ft_hash(str[i]), tmp);
			else
				ft_push_back(&head, str[i], tmp);
			free(tmp);
			while (str[i] && ft_strchr(delims, str[i]))
				i++;
			if (str[i])
				token_start = i;
		}
	}
	return (head);
}