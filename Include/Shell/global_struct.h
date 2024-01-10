#ifndef 	GLOBAL_STRUCT_H
# define 	GLOBAL_STRUCT_H

# include	"executor_struct.h"
# include 	"lexer_struct.h"
# include 	"parser_struct.h"
# include 	"sematic_struct.h"
# include 	"tokenizer_struct.h"


typedef void (*t_function_callback)();

typedef struct s_function_entity    t_function_entity;
typedef struct s_function_table     t_function_table;

struct s_function_entity
{
    char						*key;
    t_function_callback 		function;
    struct s_function_entity	*next;
};

struct s_function_table
{
    t_function_entity	**table;
    size_t 				size;
    size_t 				capacity;
};

#endif