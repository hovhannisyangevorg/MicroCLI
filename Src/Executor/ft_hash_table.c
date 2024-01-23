/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:42:38 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/19 19:59:06 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_hash_table *ft_init_hash_table(size_t initialCapacity, t_hash_type type)
{
	size_t			i;
    t_hash_table	*table;

	table = (t_hash_table *)malloc(sizeof(t_hash_table));
    table->size = 0;
    table->capacity = initialCapacity;
    if (!initialCapacity)
	    table->table = NULL;
    else
	{
		i = 0;
		table->table = malloc(initialCapacity * sizeof(t_hash_entity_list));
		while (i < initialCapacity)
			ft_init_entity_list(&table->table[i++]);
	}
    table->type = type;
    return (table);
}

void  ft_init_entity_list(t_hash_entity_list* list)
{
    list->size = 0;
	list->head = NULL;
	list->tail = NULL;
}

size_t ft_hash_entity(size_t capacity, char *key)
{
	size_t i;
    size_t hashValue;

	i = 0;
	hashValue = 0;
    while (i < ft_strlen(key))
        hashValue += key[i++];
    return (hashValue % capacity);
}

t_function_entity	*ft_create_function_entity(char *key, void *data)
{
	t_function_entity	*node;

	node			= (t_function_entity *)malloc(sizeof(t_function_entity));
    node->function	= (t_function_callback)data;
	node->base.key	= ft_strdup(key);
	node->base.next	= NULL;
	return (node);
}

t_env_entity	*ft_create_env_entity(char *key, void *data)
{
	t_env_entity	*node;

	node			= (t_env_entity *)malloc(sizeof(t_env_entity));
    node->value		= ft_strdup((char *)data);
	node->base.key	= ft_strdup(key);
	node->base.next	= NULL;
	return (node);
}


void	ft_push_entity(t_hash_entity_list *lst, char *key, void *data, t_hash_type type)
{
	t_hash_entity	*node;

    if (type == FUNCTION)
		node = ft_function_to_entity(ft_create_function_entity(key, data));
    else
		node = ft_env_to_entity(ft_create_env_entity(key, data));

	if (!lst->head)
	{
		lst->head = node;
		lst->tail = node;
		++lst->size;
		return ;
	}
	node->next	= lst->head;
	lst->head	= node;
	++lst->size;
}

void ft_resize_entity(t_hash_table *table, size_t new_capacity)
{
	size_t			i;
	t_hash_entity	*node;
    t_hash_table	*hash_table;
	char			*key;
	void			*data;
	size_t			index;

    i = 0;
    hash_table = ft_init_hash_table(new_capacity, table->type);
    while (i < table->capacity)
    {
        node = table->table[i].head;
        while (node)
        {
            key = node->key;
            index = ft_hash_entity(new_capacity, key);
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

void	ft_insert_entity(t_hash_table *table, char *key, void *data)
{
	size_t index;
	size_t newCapacity;

    if (!table)
        return ;
    if (table->size >= table->capacity)
	{
		if (!table->capacity)
			newCapacity = 10;
        else
            newCapacity = table->capacity * 2;
        ft_resize_entity(table, newCapacity);
    }

    index = ft_hash_entity(table->capacity, key);
	ft_push_entity(&table->table[index], key, data, table->type);
    table->size++;
}

t_function_callback	ft_get_function(t_hash_table *table, char *key)
{
    size_t			index;
	t_hash_entity	*entry;

	index = ft_hash_entity(table->capacity, key);
    entry = table->table[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return (ft_entity_to_function(entry)->function);
        entry = entry->next;
    }
    return (NULL);
}

char* ft_get_env(t_hash_table *table, char *key)
{
    size_t			index;
    t_hash_entity	*entry;

	index = ft_hash_entity(table->capacity, key);
	entry = table->table[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return (ft_entity_to_env(entry)->value);
        entry = entry->next;
    }
    return (NULL);
}


void	ft_set_env(t_hash_table *table, char *key, char *val)
{
    size_t			index;
    t_hash_entity	*entry;
	t_env_entity	*ent_tmp;

	index = ft_hash_entity(table->capacity, key);
	entry = table->table[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
        {
			ent_tmp = ft_entity_to_env(entry);
			free(ent_tmp->value);
			ent_tmp->value = ft_strdup(val);
			return ;
		}
        entry = entry->next;
    }
	ft_insert_entity(table, key, val);
}


void	print_env(t_hash_table* env)
{
    size_t 			i;
	t_hash_entity 	*entry;
	t_env_entity	*node;

	i = 0;
    while(i < env->capacity)
    {

        entry = env->table[i].head;
        while (entry != NULL)
        {
            node	= ft_entity_to_env(entry);
            printf("%s=%s\n", entry->key, node->value);
            entry	= entry->next;
        }
        ++i;
    }
}


t_hash_table *ft_create_env(char **env)
{
	size_t			i;
	size_t			len;
	t_hash_table	*table;
	char			*assign;
	char			*value;
	char			*key;

	i = 0;
	table = ft_init_hash_table(0, ENV);
	while (env && env[i])
	{
		assign = ft_strchr(env[i], '=');
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
		key = ft_substr(env[i], 0, len);
		ft_insert_entity(table, key, value);
		++i;
	}
	return (table);
}
