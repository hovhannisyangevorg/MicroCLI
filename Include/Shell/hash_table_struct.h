#ifndef HASH_TABLE_STRUCT_H
#define HASH_TABLE_STRUCT_H

#include <stddef.h>

enum e_hash_type
{
    FUNCTION,
    ENV
};

typedef struct s_hash_entity t_hash_entity;
typedef struct s_hash_entity_list t_hash_entity_list;
typedef struct s_hash_table t_hash_table;
typedef enum e_hash_type t_hash_type;

typedef void (*t_function_callback)();

typedef struct s_function_entity        t_function_entity;

typedef struct s_env_entity             t_env_entity;



struct s_hash_entity
{
    char*            key;
    t_hash_entity*   next;
};

struct s_hash_entity_list
{
    t_hash_entity*  head;
    t_hash_entity*  tail;
    size_t          size;
};


struct s_hash_table
{
    t_hash_type         type;
    t_hash_entity_list* table;
    size_t              size;
    size_t              capacity;
};


/*
 * types of hash table values
 * 1 function table 
 * 2 envirement table
*/
struct s_function_entity
{
    t_hash_entity           base;
    t_function_callback     function;
};

struct s_env_entity
{
    t_hash_entity           base;
    char*                   value;
};




#endif