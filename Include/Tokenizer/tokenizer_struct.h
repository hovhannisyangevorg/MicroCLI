/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:57:11 by gehovhan          #+#    #+#             */
/*   Updated: 2023/10/21 15:16:34 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		TOKENIZER_STRUCT_H
# define	TOKENIZER_STRUCT_H


#define SEPARARTORS ";|&<>()" // || >> << &&
#define RED "\033[31m"
#define BLACK "\033[30m"
#define GREEN "\033[32m"

typedef struct	s_stack		t_stack;
typedef struct	s_node		t_node;
typedef struct	s_token		t_token;

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
	size_t	size;
	t_token	*next;
};

#endif
