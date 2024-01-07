/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:57:11 by gehovhan          #+#    #+#             */
/*   Updated: 2023/12/21 14:45:43 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		TOKENIZER_STRUCT_H
# define	TOKENIZER_STRUCT_H


# define 	SEPARATORS 		";|&<>()"
//;|&<>
# define 	OPERATORS 		";|&"
# define 	RED 				"\033[31m"
# define 	BLACK 				"\033[30m"
# define 	GREEN 				"\033[32m"

typedef struct	s_stack			t_stack;
typedef struct	s_node			t_node;
typedef struct	s_token			t_token;
typedef struct	s_list_token	t_list_token;

struct s_node
{
	char data;
	t_node *next;
};

struct s_stack
{
	t_node *top;
};

struct s_token
{
	t_token_type		type;
	char				*token;
	int 				quate_type;
	t_token				*next;
	t_token 			*prev;
};

struct s_list_token
{
	t_container		base;
	t_token			*head;
	t_token			*tail;
	size_t			size;
};

#endif























//      sort -nr -k 5 <( ls -l /bin ) <( ls -l /usr/bin ) <( ls -l /sbin )
//      comm -12 <( sort file1 ) <( sort file2 )