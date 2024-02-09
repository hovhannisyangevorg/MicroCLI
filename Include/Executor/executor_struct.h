#ifndef 	EXECUTOR_STRUCT_H
# define 	EXECUTOR_STRUCT_H

#include "parser_struct.h"
#include "tokenizer_struct.h"


typedef enum 	e_exec_type			t_exec_type;
typedef struct	s_hash_entity		t_hash_entity;
typedef struct	s_hash_entity_list	t_hash_entity_list;
typedef struct	s_entity_table		t_entity_table;
typedef enum	e_hash_type			t_hash_type;
typedef struct 	s_hash_table 		t_hash_table;
typedef struct 	s_vector			t_vector;


typedef int (*t_function_callback)();

typedef struct s_function_entity        t_function_entity;

typedef struct s_env_entity             t_env_entity;

typedef struct s_hash_table_arr         t_hash_table_arr;




enum e_exec_type
{
	LIST = 1L << 0,
	TREE = 1L << 1
};

enum e_hash_type
{
    FUNCTION,
    ENV
};

struct s_hash_entity
{
    char			*key;
    t_hash_entity	*next;
};

struct s_hash_entity_list
{
    t_hash_entity*  head;
    t_hash_entity*  tail;
    size_t          size;
};


struct s_entity_table
{
    t_hash_type         type;
    t_hash_entity_list* entity;
    size_t              size;
    size_t              capacity;
};

struct s_hash_table
{
	t_entity_table* table;
};

struct s_function_entity
{
    t_hash_entity           base;
    t_function_callback     function;
};

struct s_env_entity
{
    t_hash_entity           base;
    int                     hidden;
    char*                   value;
};


struct s_hash_table_arr
{
    char**  table;
    size_t  size;
};


struct s_vector
{
	int			*arr;
	size_t		size;
	size_t		capacity;
};

#endif