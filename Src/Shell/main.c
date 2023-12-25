/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/12/25 21:40:40 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_program()
{
	char 			*line;
	t_list_token	*list;

	signal(SIGINT, sig_handler_c);
	rl_catch_signals = 0;
	while (1)
	{
		line = ft_get_line();
		if (!line)
			return ;
		ft_brackets_balanced(line);
		list = ft_multi_split(line, SEPARARTORS, 0);
		if (list->size != 0){
			ft_ordering(list);
		}
		// ft_push_front(list, 0, ft_strdup("START"));
		ft_split_token(list);
		// ft_push_back(list, 0, ft_strdup("END"));
		ft_print_list(*list);
		
		ft_parser(list);
		ft_free_list(list);
		free(line);
    }
    clear_history();
}

// case         (()()()()()()()()()()()()()()()()()()()()()()()()()()()()) | (()()()()()()()()()()()())

int main()
{
	// t_token t;
	// ft_init_token(&t, TEXT, "(ls | (grep) (hi))");
	// t_ast_node* node = ft_create_ast_node(&t);
	// node = ft_correct_subshell(node);
	// ft_ast_print(node, ft_strdup(""), 0, 1);
	// fixaca
	// myus casenel jogaca hopar
	// ft_substr("(()()()()()()()()()()()()()()()()()()()()()()()()()()()())")
	ft_program();
	return (0);	
}














