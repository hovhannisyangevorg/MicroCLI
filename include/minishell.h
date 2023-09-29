/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:23:33 by gehovhan          #+#    #+#             */
/*   Updated: 2023/09/27 16:10:16 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"
# include "shell_struct.h"
# include "shell_struct.h"

/**
* File: ft_stack_method.c
* Description: This file contains the implementation of the following functions.
*/
t_stack *ft_initialize_stack();
int 	ft_is_empty(t_stack *stack);
void	ft_push_stack(t_stack *stack, char item);
char 	ft_pop_stack(t_stack *stack);
void 	ft_free_stack(t_stack *stack);

/**
* File: ft_parenthes_balancer.c
* Description: This file contains the implementation of the following functions.
*/
void ft_is_balanc(char *expression);






void ft_check_quote(char *expression);


#endif