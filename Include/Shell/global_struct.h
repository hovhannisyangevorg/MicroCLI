#ifndef 	GLOBAL_STRUCT_H
# define 	GLOBAL_STRUCT_H

# include	"executor_struct.h"
# include 	"lexer_struct.h"
# include 	"parser_struct.h"
# include 	"sematic_struct.h"
# include 	"tokenizer_struct.h"
# include <termios.h>

typedef struct 	s_container			t_container;

typedef struct s_global_state		t_global_state;

struct s_container
{
	t_exec_type 	exec_type;
	t_io 			fd;
	t_status_codes	exit_status;
	t_symbol_table*	table;
	union
	{
		t_global_tree 	*tree;
		t_command		*command;
	};
};



struct s_global_state
{
	struct termios	orig_termios;
	t_signal_type	minishell_signal;
};

extern t_global_state g_global_state;



#endif