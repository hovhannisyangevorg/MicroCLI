/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:57:11 by gehovhan          #+#    #+#             */
/*   Updated: 2023/11/01 21:37:45 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		TOKENIZER_STRUCT_H
# define	TOKENIZER_STRUCT_H


# define 	SEPARARTORS 		";|&<>()"
# define 	RED 				"\033[31m"
# define 	BLACK 				"\033[30m"
# define 	GREEN 				"\033[32m"

typedef struct	s_stack			t_stack;
typedef struct	s_node			t_node;
typedef struct	s_token			t_token;
typedef enum	e_token_types	t_token_types;
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
	int		type;
	char	*token;
	int 	quate_flags;
	t_token	*next;
	t_token *prev;
};

struct s_list_token
{
	t_token *head;
	t_token *tail;
	size_t	size;
};


enum e_token_types
{
	NNULL,
	TEXT	= 1000,
	PIPE	= 124,
	OR		= -124,
	AMP		= 34,
	AND		= -34,
	SEMI	= 59,
	SEMITWO = -59
};

#endif
