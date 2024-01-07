#ifndef 	EXECUTOR_STRUCT_H
# define 	EXECUTOR_STRUCT_H


typedef enum e_container_type t_container_type;

typedef struct s_container t_container;

/*
 * handler function for executing command interpreter
 * used in list or syntax tree
 * ft_ast_methods.c or ft_list_mothods.c
*/
typedef void (*t_execute_handler)();

enum e_container_type
{
    LIST,
    SYNTAX_TREE
};

/*
 * abstraction for executor
 * handle with list or abstract syntax tree
 * handler set in list or syntax tree structure
 * ft_ast_methods.c or ft_list_mothods.c
*/
struct s_container
{
    t_container_type    type;
    t_execute_handler   handler;
};



#endif