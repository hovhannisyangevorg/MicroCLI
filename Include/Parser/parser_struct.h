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


#include "executor_struct.h"

/**
 * @typedef t_ast_node
 * @brief Represents a node in the abstract syntax tree (AST).
 */
typedef struct	s_ast_node		t_ast_node;

typedef	struct	s_command		t_command;
typedef	struct	s_argument		t_argument;
typedef	struct	s_redirect		t_redirect;

/**
 * @typedef t_token_type
 * @brief Enumerates different token types.
 */
typedef enum	e_token_type	t_token_type;

/**
 * @typedef t_token_type
 * @brief Enumerates different token types mapping.
 */
typedef enum	e_token_map_type	t_token_map_type;

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


typedef	enum e_io_type			t_io_type;
typedef enum e_redirect_side	t_redirect_side;
// typedef void (*t_callback)(t_list_token* list);

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
	TEXT		= 1L << 0,
	PIPE		= 1L << 1,
	OR			= 1L << 2,
	JOB			= 1L << 3,
	AND			= 1L << 4,
	SEMI		= 1L << 5,
	SEMITWO 	= 1L << 6,
	OPBREK		= 1L << 7,
	CLBREK		= 1L << 8,
	WRITE		= 1L << 9,
	READ		= 1L << 10,
	APPEND		= 1L << 11,
	HEREDOC		= 1L << 12,
	SUBSHELL 	= 1L << 13,
	COMMAND		= 1L << 14,
	REDIRECT	= 1L << 15,
	ARGUMENT	= 1L << 16,
	ROOT		= 1L << 17
};


enum e_redirect_side
{
	NEXT_BRACE = 1L << 0,
	PREV_BRACE = 1L << 1
};

enum e_io_type
{
	STDIN = 1L << 0,
	STDOUT = 1L << 1,
	STDERR = 1L << 2
};

enum e_token_map_type
{
	MNNULL,
	MTEXT		= 1000,
	MPIPE		= 124,
	MOR			= -124,
	MJOB		= 38,
	MAND		= -38,
	MSEMI		= 59,
	MSEMITWO 	= -59,
	MOPBREK		= 40,
	MCLBREK		= 41,
	MWRITE		= 62,
	MREAD		= 60,
	MAPPEND		= -62,
	MHEREDOC	= -60
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
