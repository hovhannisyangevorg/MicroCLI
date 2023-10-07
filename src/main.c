/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/10/07 19:13:49 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Victory belongs to anyone who perseveres on any path.
 */

#include "minishell.h"

// typedef enum s_quot
// {
// 	SINGL 	= 0x0001,
// 	DOUBLE 	= 0x1000,
// } t_quot;

// t_token	*ft_quot(char *start, int flag)
// {
// 	printf("------------%c\n", *start);
// 	printf("%d\n", flag);

// 	// while ()
// 	// {
// 	// }
// 	return (0);
// }

// t_token	*ft_check_quote(char *expression)
// {
// 	int flag;
// 	char *tmp;
// 	t_token *token;

// 	flag = 0;
// 	token = 0;
// 	tmp = expression;
// 	while (tmp && *tmp)
// 	{
// 		if (*tmp == '\"')
// 			flag |= DOUBLE;
// 		else if (*tmp == '\"')
// 			flag |= SINGL;
// 		printf("%d\n", flag);
// 		if (flag == DOUBLE)
// 			token = ft_quot(tmp, flag);
// 		else if (flag == SINGL)
// 			token = ft_quot(tmp, flag);

// 		tmp++;
// 		flag = 0;
// 	}
// 	return (token);
// }

int main()
{
	int i;
	char *line;
	char **spled;

	signal(SIGINT, sig_handler_c);
	rl_catch_signals = 0;
	while (1)
	{
		i = 0;
		line = ft_get_line();
		if (!line)
			return (0);
		spled = ft_multi_split(line, SEPARARTORS);
		// while (spled[i])
		// {
		// 	printf("%s", spled[i]);
		// 	i++;
		// }
		ft_vecstrdel(&spled);
		free(line);
    }
    clear_history();
    return (0);
}





