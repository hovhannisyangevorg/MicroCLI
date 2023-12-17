/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/12/17 16:37:15 by gevorg           ###   ########.fr       */
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

int main()
{
	ft_program();
	return (0);	
}











































































// union test
// {
// 	char 	x;
// 	int 	d;
// 	int 	o;
// 	float 	y;
// };

// static int	ft_find_index(char *expression, int index)
// {
// 	int i;
	
// 	t_stack *stack;
// 	stack = ft_initialize_stack();
// 	// t_stack *stack2;
// 	// stack2 = ft_initialize_stack();
// 	i = 0;
// 	while (expression && expression[i])
// 	{
// 		if (expression[i] == '(')
// 		{
// 			// ft_push_stack(stack, '(');
// 			ft_push_stack(stack, i);
// 		}
// 		else if (expression[i] == ')')
// 		{
// 			if (stack->top)
// 			{
// 				int res = stack->top->data;
// 				printf("%d\n", res);
// 				if (res == index)
// 					return i;
// 			}
// 			ft_pop_stack(stack);
// 			// if (c != '(')
// 			// {
// 			// 	ft_free_stack(stack);
// 			// 	free(stack);
// 			// 	return (0);
// 			// }
// 		}
// 		++i;
	
// 	}
// 	ft_free_stack(stack);
// 	free(stack);
// 	return -1;
// }



// int main()
// {
// 	// char *p = "((dsadasdsa(dsadas)))";
// 	// printf("%d\n", ft_find_index(p, 1));
// 	ft_program();
// 	return (0);	
// }

