/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:23:33 by gehovhan          #+#    #+#             */
/*   Updated: 2023/10/18 21:47:24 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "libft.h"
# include "shell_struct.h"
/**
* @file: ft_stack_method.c
* Description: This file contains the implementation of the following functions.
*/
t_stack *ft_initialize_stack();
int 	ft_is_empty(t_stack *stack);
void	ft_push_stack(t_stack *stack, char item);
char 	ft_pop_stack(t_stack *stack);
void 	ft_free_stack(t_stack *stack);

/**
* @file: ft_parenthes_balancer.c
* Description: This file contains the implementation of the following functions.
*/
void ft_is_balanc(char *expression);


void	ft_check_quote(t_token *token);


/**
* @file: ft_list_method.c
* Description: This file contains the implementation of the following functions.
*/
void	ft_init_list(t_token **head);
void	ft_push_back(t_token **head, int type, const char *token);
void	ft_push_front(t_token **head, int type, const char *token);
void	ft_pop_back(t_token **head);
void	ft_pop_front(t_token **head);
void	ft_free_list(t_token **head);
void	ft_print_list(t_token *head);


// ft_multi_split.c
t_token	*ft_multi_split(char* str, char* delims);

// ft_get_line.c
char	*ft_get_line();
void	sig_handler_c(int signum);

#endif


















/*
* bash: syntax error near unexpected token `('
*
*/