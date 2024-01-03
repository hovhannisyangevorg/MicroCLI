/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2024/01/03 20:53:41 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stddef.h>

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
        list = ft_tokenize(line, SEPARATORS);
		ft_print_list(list->head);
		ft_parser(list);
		ft_free_list(list);
		free(line);
    }
    clear_history();
}

typedef struct shape
// {
// 	double 	g;		//	8
// 	int 	x;		//	8
// 	char 	y;		//	8
// 	short 	t;		
// 	char 	f;		
// } t_shape;

// typedef struct rect
// {
// 	int x;
// 	// int y;
// 	// t_shape base;
// 	// double j;
// } t_rect;

// composition 
int main()
{
	// printf("%lu\n", sizeof(t_shape));
	// t_rect r;
	// r.x = 8;
	// // r.y = 9;
	// t_shape* s = (t_shape* )&r;

	// printf("%d\n", s->x);
	
	ft_program();
	return (0);	
}

































// #include <stdio.h>
// #include <string.h>

// char	*strtok_custom(char *str, const char *delim)
// {
// 	char 			*start;
//     static char 	*next_token = NULL;
	
// 	if (!str && !next_token)
// 		return (NULL);
// 	if (str)			//
// 		next_token = str;
// 	while (*next_token && strchr(delim, *next_token))
//         ++next_token;
// 	if (!*next_token) {
//         next_token = NULL;
//         return NULL;
//     }

//     start = next_token;
//     while (*next_token && !strchr(delim, *next_token))
// 		++next_token;
	
//     if (*next_token) {
//         *next_token = '\0';
//         ++next_token;
//     } else
// 		next_token = NULL;

//     return (start);
// }

// int main() {
//     char str[] = "Hello,Armeina,atatt,,,,,";
//     const char delim[] = ",";
//     char *token;

//     token = strtok_custom(str, delim);
	
// 	printf("%s\n", token);
//     while (token != NULL) {
//         printf("%s\n", token);
//         token = strtok_custom(NULL, delim);
//     }

//     return 0;
// }












