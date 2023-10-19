/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/10/18 21:21:49 by gevorg           ###   ########.fr       */
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





// struct s_token
// {
// 	int		type;
// 	char	*token;
// 	int 	quate_flags;
// 	size_t	size;
// 	t_token	*next;
// };

// int ft_quote_count()
// {

// }

// void	ft_check_quote(t_token *head)
// {
// 	t_token *tmp;

// 	tmp = head;
		
// 	while (tmp)
// 	{
// 		// if (tmp->token == '\"')
// 		// 	flag |= DOUBLE;
// 		// else if (*tmp == '\"')
// 		// 	flag |= SINGL;
// 		// printf("%d\n", flag);
// 		// if (flag == DOUBLE)
// 		// 	token = ft_quot(tmp, flag);
// 		// else if (flag == SINGL)
// 		// 	token = ft_quot(tmp, flag);
// 		tmp = tmp->next;
// 	}

// }

// printf("1\n");



















int main()
{
	char *line;
	t_token *head;

	signal(SIGINT, sig_handler_c);
	rl_catch_signals = 0;
	while (1)
	{
		line = ft_get_line();
		ft_is_balanc(line);
		if (!line)
			return (0);
		head = ft_multi_split(line, SEPARARTORS);
		// ft_check_quote(head);

		
		ft_print_list(head);
		ft_free_list(&head);
		free(line);
    }
    clear_history();
    return (0);
}





