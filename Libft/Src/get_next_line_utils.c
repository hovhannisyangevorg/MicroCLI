/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:09:38 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/26 20:36:30 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_strlen(const char *s)
{
	size_t	index;

	index = 0;
	if (!s)
		return (0);
	while (s[index])
		++index;
	return (index);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char		*new_str;
	size_t		f_index;
	size_t		s_index;

	new_str = malloc(sizeof(char) * (ft_gnl_strlen(s1) + \
				ft_gnl_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	f_index = 0;
	s_index = 0;
	if (s1)
		while (s1[f_index])
			new_str[s_index++] = s1[f_index++];
	f_index = 0;
	if (s2)
		while (s2[f_index])
			new_str[s_index++] = s2[f_index++];
	new_str[s_index] = '\0';
	if (s1)
		free(s1);
	return (new_str);
}

int	ft_gnl_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	while (s[index])
	{
		if (s[index] == c)
			return (1);
		++index;
	}
	return (0);
}
