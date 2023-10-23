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

<<<<<<< HEAD:Include/Tokenizer/tokenizer_struct.h
#ifndef		TOKENIZER_STRUCT_H
# define	TOKENIZER_STRUCT_H
=======


#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H
>>>>>>> d87676c0f4a9627384897b952b54dc3ef0b83cdc:include/shell_struct.h


<<<<<<< HEAD:Include/Tokenizer/tokenizer_struct.h
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
=======

#define HEADER \
"\e[38;2;3;97;0m""\
###########################################################################\n\
#                                                                         #\n\
#   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗        #\n\
#   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║        #\n\
#   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║        #\n\
#   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        #\n\
#   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗   #\n\
#   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   #\n\
#                                                                         #\n\
###########################################################################\e[0m"



// struct function_cmd
// {
// 	char *cmd;
// 	command_t func;
// };

// function_cmd table[6];

// struct s_main
// {
	
// };
>>>>>>> d87676c0f4a9627384897b952b54dc3ef0b83cdc:include/shell_struct.h

#endif
