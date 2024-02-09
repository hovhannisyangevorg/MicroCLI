#ifndef 	GLOBAL_STRUCT_H
# define 	GLOBAL_STRUCT_H

# include	"executor_struct.h"
# include 	"lexer_struct.h"
# include 	"parser_struct.h"
# include 	"sematic_struct.h"
# include 	"tokenizer_struct.h"

typedef struct 	s_container			t_container;

struct s_container
{
	t_exec_type 	exec_type;
	t_io 			fd;
	t_status_codes	exit_status;
	union
	{
		t_global_tree 	*tree;
		t_command		*command;
	};
};

// extern size_t numofrec;

#endif