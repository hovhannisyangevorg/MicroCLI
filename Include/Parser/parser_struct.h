/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:44:21 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/24 20:48:53 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	PARSER_STRUCT_H
# define 	PARSER_STRUCT_H


/**
 * @typedef t_ast_node
 * @brief Represents a node in the abstract syntax tree (AST).
 */
typedef struct	s_ast_node		t_ast_node;

/**
 * @typedef t_token_type
 * @brief Enumerates different token types.
 */
typedef enum	e_token_type	t_token_type;

/**
 * @typedef t_quot_type
 * @brief Enumerates different quotation types.
 */
typedef enum	e_quot_type		t_quot_type;

/**
 * @typedef t_global_tree
 * @brief Represents the global abstract syntax tree (AST).
 */
typedef struct	s_global_tree	t_global_tree;

/**
 * 
 * Stack structure of the Shunting Yard algorithm.
 * 
 * This structs introduces two stack structures for 
 * handling abstract syntax trees (AST) during expression parsing.
*/
typedef struct	s_global_stack	t_global_stack;
typedef struct	s_shant_stack	t_shant_stack;


/**
 * @enum e_token_type
 * @brief Enumerates different token types.
 * 
 * Values:
 * - NNULL: Null token type.
 * - TEXT: Text token type.
 * - PIPE: Pipe token type.
 * - OR: Logical OR token type.
 * - AMP: Ampersand token type.
 * - AND: Logical AND token type.
 * - SEMI: Semi token type.
 * - SEMITWO: Two semi token type.
 */
enum e_token_type
{
	NNULL,
	TEXT		= 1000,
	PIPE		= 124,
	OR			= -124,
	AMP			= 38,
	AND			= -38,
	SEMI		= 59,
	SEMITWO 	= -59,
	OPBREK		= 40,
	CLBREK		= 41,
	SUBSHELL 	= 500
};

enum e_quot_type
{
	UNQUOT		= 0,
	SINGL		= 27,
	DOUBLE		= 22
};

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

struct s_global_tree
{
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
