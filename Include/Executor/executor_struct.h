#ifndef 	EXECUTOR_STRUCT_H
# define 	EXECUTOR_STRUCT_H

#include "parser_struct.h"
#include "tokenizer_struct.h"

typedef enum 	e_exec_type		t_exec_type;
typedef struct 	s_container		t_container;

enum e_exec_type
{
	LIST = 1L << 0,
	TREE = 1L << 1
};

struct s_container
{
	t_exec_type 	exec_type;
	union 
	{
		t_global_tree 	*tree;
		t_list_token	*list;
	};
};



#endif