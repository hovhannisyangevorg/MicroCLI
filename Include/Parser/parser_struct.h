/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:44:21 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/03 21:00:57 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	PARSER_STRUCT_H
# define 	PARSER_STRUCT_H

# include "parser_types.h"

struct s_ast_node
{
    t_token_type	token_type;
	t_quot_type		quate_type;
    char			*token;
    t_ast_node		*left;
    t_ast_node		*right;
	t_ast_node		*parent;
	t_global_stack	*subshell;
};

/*
 * every command should have io file descriptors for transfer one to other
*/
struct s_command
{
	t_ast_node	base;
	t_argument	*argument;
	t_redirect	*redirect;
	t_io		io;
};

struct s_argument
{
	t_ast_node	base;
	char**		arguments;
};

struct s_redirect
{
	t_ast_node		base;
	t_redirect_side	side;
	char			*argument;
};

struct s_global_tree
{
	t_container		base;
	t_ast_node 		*ast_node;
	size_t 			tree_size;
};

struct s_global_stack
{
	t_shant_stack	*top;
	size_t 			size;
};

struct s_shant_stack
{
	t_ast_node		*ast_node;
	t_shant_stack 	*next;
};

#endif
