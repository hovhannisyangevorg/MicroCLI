#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "hash_table_struct.h"


t_function_entity*  ft_entity_to_function(t_hash_entity* hash);

t_env_entity*       ft_entity_to_env(t_hash_entity* hash);


t_hash_entity*      ft_function_to_entity(t_function_entity* func);

t_hash_entity*      ft_env_to_entity(t_env_entity* env);




t_hash_table*       ft_init_hash_table(size_t initialCapacity, t_hash_type type);

void                ft_init_entity_list(t_hash_entity_list* lst);

size_t              ft_hash_entity(size_t capacity, char* key);


void                ft_push_entity(t_hash_entity_list* lst, char* key, void* data, t_hash_type type);

void                ft_insert_entity(t_hash_table* table, char* key, void* data);

t_function_callback ft_get_function(t_hash_table* table, char* key);

char*               ft_get_env(t_hash_table* table, char* key);

t_hash_table*       ft_create_env(char** env);

void                print_env(t_hash_table* env);

#endif