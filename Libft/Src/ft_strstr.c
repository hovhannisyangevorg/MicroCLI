/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:13:14 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/19 16:13:16 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int h_index;
	int n_index;

	h_index = 0;
	if (!*needle)
		return ((char*)haystack);
	while (haystack[h_index])
	{
		n_index = 0;
		if (haystack[h_index] == needle[n_index])
		{
			while (haystack[h_index + n_index] == needle[n_index])
			{
				if (needle[n_index + 1] == '\0')
					return ((char*)&haystack[h_index]);
				++n_index;
			}
		}
		++h_index;
	}
	return (0);
}