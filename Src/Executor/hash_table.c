#include "shell.h"


t_hash_table* ft_init_hash_table(size_t initialCapacity, t_hash_type type)
{
    t_hash_table* table = (t_hash_table*)malloc(sizeof(t_hash_table));
    table->size = 0;
    table->capacity = initialCapacity;
    if (!initialCapacity)
	    table->table = NULL;
    else
       table->table = malloc(initialCapacity * sizeof(t_hash_entity_list));
    table->type = type;
    return table;
}

void  ft_init_entity_list(t_hash_entity_list* lst)
{
    lst->size = 0;
	lst->head = NULL;
	lst->tail = NULL;
}

void  ft_init_entity_list2(t_hash_entity_list* lhs, t_hash_entity_list* rhs)
{
    lhs->size = rhs->size;
	lhs->head = rhs->head;
	lhs->tail = rhs->tail;
}

size_t ft_hash_entity(size_t capacity, char* key)
{
    size_t hashValue = 0;
    for (size_t i = 0; i < ft_strlen(key); ++i)
    {
        hashValue += key[i];
    }
    return hashValue % capacity;
}

t_function_entity* ft_create_function_entity(char* key, void* data)
{
	t_function_entity* node;

	node = malloc(sizeof(t_function_entity));
    node->function = (t_function_callback)data;
	node->base.key = ft_strdup(key);
	node->base.next = NULL;
	return node;
}

t_env_entity* ft_create_env_entity(char* key, void* data)
{
	t_env_entity* node;

	node = malloc(sizeof(t_env_entity));
    node->value = ft_strdup((char*)data);
	node->base.key = ft_strdup(key);
	node->base.next = NULL;
	return node;
}


void ft_push_entity(t_hash_entity_list* lst, char* key, void* data, t_hash_type type)
{
	t_hash_entity* node;
	
    if (type == FUNCTION)
	    node = ft_function_to_entity(ft_create_function_entity(key, data));
    else
    {
        node = ft_env_to_entity(ft_create_env_entity(key, data));

    }
	if (!lst->head)
	{
		lst->head = node;
		lst->tail = node;
		++lst->size;
		return;
	}
	node->next = lst->head;
	lst->head = node;
	++lst->size;
}

void ft_resize_entity(t_hash_table* table, size_t new_capacity)
{
    t_hash_table* hash_table;

    hash_table = ft_init_hash_table(new_capacity, table->type);
    t_hash_entity_list* newTable = (t_hash_entity_list *)malloc(new_capacity * sizeof(t_hash_entity_list));
    if (!newTable)
        return ;
    size_t i = 0;
    while (i < table->capacity)
    {
        ft_init_entity_list(&hash_table->table[i]);
        t_hash_entity* node = table->table[i].head;
        while (node)
        {
            char* key = node->key;
            size_t index = ft_hash_entity(new_capacity, key);
            void* data;
            if (table->type == FUNCTION)
                data = ft_entity_to_function(node)->function;
            else
                data = ft_entity_to_env(node)->value;
            ft_push_entity(&hash_table->table[index], key, data, table->type);
            node = node->next;
        }
        ++i;
    }
    free(table->table);
    table->table = hash_table->table;
    table->capacity = new_capacity;
    free(hash_table);
}

void ft_insert_entity(t_hash_table* table, char* key, void* data)
{
    if (!table)
        return ;
    if (table->size >= table->capacity)
	{
        size_t newCapacity;
		if (!table->capacity)
			newCapacity = 10;
        else
            newCapacity = table->capacity * 2;
        ft_resize_entity(table, newCapacity);
    }

    size_t index = ft_hash_entity(table->capacity, key);
	ft_push_entity(&table->table[index], key, data, table->type);
    table->size++;
}

t_function_callback ft_get_function(t_hash_table* table, char* key)
{
    size_t index = ft_hash_entity(table->capacity, key);

    t_hash_entity* entry = table->table[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return ft_entity_to_function(entry)->function;
        entry = entry->next;
    }
    return NULL;
}

char* ft_get_env(t_hash_table* table, char* key)
{
    size_t index = ft_hash_entity(table->capacity, key);
    t_hash_entity* entry = table->table[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return ft_entity_to_env(entry)->value;
        entry = entry->next;
    }
    return NULL;
}


void print_env(t_hash_table* env)
{
    size_t i = 0;
    while(i < env->capacity)
    {

        t_hash_entity* entry = env->table[i].head;
        while (entry != NULL)
        {
            t_env_entity* node = ft_entity_to_env(entry);
            printf("%s=%s\n", entry->key, node->value);
            entry = entry->next;
        }
        ++i;
    }
}


t_hash_table* ft_create_env(char** env)
{
	t_hash_table* table;

	table = ft_init_hash_table(0, ENV);
	size_t i = 0;
	while (env && env[i])
	{
		char* assign = ft_strchr(env[i], '=');
		char* value;
		size_t len;
		if (assign)
		{
			len = assign - env[i];
			value = assign + 1;
		}
		else
		{
			len = ft_strlen(env[i]);
			value = "";
		}
		char *key = ft_substr(env[i], 0, len);
		ft_insert_entity(table, key, value);
		++i;
	}
	return table;
}