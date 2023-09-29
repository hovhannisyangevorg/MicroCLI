/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sindob_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:46:04 by gevorg            #+#    #+#             */
/*   Updated: 2023/09/28 18:19:45 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum s_quot
{
	SINGL 	= 0x0001,
	DOUBLE 	= 0x1000,
} t_quot;


// struct s_token
// {
// 	int type;
// 	char *token;
// 	t_token *next;
// };

// char *ft_quot(char *expression)
// {
	
// }



// void	*ft_check_quote(char *expression)
// {
// 	int flag;
// 	flag = 0;

// 	while (expression && *expression)
// 	{
// 		if (*expression == '\"')
// 			flag |= DOUBLE;
// 		else if (*expression == '\"')
// 			flag |= SINGL;
// 		// printf("%d\n", flag);
// 		if (flag == DOUBLE)
// 			ft_quot(flag);
// 		else if (flag == DOUBLE)
// 			ft_quot(flag);

// 		expression++;
// 	}
// }
