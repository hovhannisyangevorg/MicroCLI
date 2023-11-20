/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/11/20 21:09:40 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_program()
{
	char *line;
	t_list_token *list;

	signal(SIGINT, sig_handler_c);
	rl_catch_signals = 0;
	while (1)
	{
		line = ft_get_line();
		if (!line)
			return ;
		ft_is_balanc(line);
		list = ft_multi_split(line, SEPARARTORS);
		if (list->size != 0)
			ft_ordering(list);
		ft_split_token(list);
		ft_parser(list);
		// ft_print_list(*list);
		ft_free_list(list);
		free(line);
    }
    clear_history();
}

// union test
// {
// 	char 	x;
// 	int 	d;
// 	int 	o;
// 	float 	y;
// };

int main()
{
	ft_program();
	return (0);	
}

