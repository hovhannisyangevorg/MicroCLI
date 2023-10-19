/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:45:22 by gehovhan          #+#    #+#             */
/*   Updated: 2023/10/01 13:17:47 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *string, int searched_char)
{
	char	*str;

	str = string;
	while (str && *str != searched_char && *str != 0)
		str++;
	if (str && *str == searched_char)
		return (str);
	else
		return (NULL);
}
