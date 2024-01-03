/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:02:37 by gehovhan          #+#    #+#             */
/*   Updated: 2023/12/25 20:05:01 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	// char	*subst;
	// size_t	size;

	// if (!s)
	// 	return (NULL);
	// if (start >= ft_strlen(s))
	// 	return (ft_strdup(""));
	// size = ft_strlen(s + start);
	// if (size < len)
	// 	len = size;
	// subst = (char *)malloc(sizeof(char) * (len + 1));
	// if (!subst)
	// 	return (NULL);
	// ft_strlcpy(subst, s + start, len + 1);
	// return (subst);
	size_t			s_len;
	size_t			over_len;
	unsigned int	index;
	char			*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	over_len = ft_strlen(s + start);
	index = 0;
	if (len > over_len)
		len = over_len;
	if (!(str = malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (index < len && start + index < (unsigned int)s_len)
	{
		str[index] = *(s + start + index);
		++index;
	}
	str[index] = '\0';
	return (str);
}
