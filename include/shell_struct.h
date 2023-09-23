/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:57:11 by gehovhan          #+#    #+#             */
/*   Updated: 2023/09/22 17:45:03 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

/**
 * @file shell_struct.h
 * @brief Contains definitions of data structures for the Minishell project.
 */

typedef struct	s_stack		t_stack;
typedef struct	s_node		t_node;


/**
 * @struct s_node
 * 
 * @brief A structure representing a node in a singly-linked list.
 */
struct s_node
{
	char data;
	t_node *next;
};

/**
 * @struct s_stack
 * 
 * @brief A structure representing a stack data structure implemented using linked list.
 */
struct s_stack
{
	t_node *top;
};



 
#endif
