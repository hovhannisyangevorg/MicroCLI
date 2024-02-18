/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:42:38 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 19:42:24 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_partition(char **arr, int low, int high)
{
	int		j;
    int		i;
    char	*pivot = arr[high];

	j = low;
	i = low - 1;
    while (j < high)
	{
        if (ft_strcmp(arr[j], pivot) < 0)
            ft_strswap(&arr[++i], &arr[j]);
		j++;
    }
    ft_strswap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quicksort algorithm
void ft_quicksort(char **arr, int low, int high)
{
    if (low < high)
	{
        int pi = ft_partition(arr, low, high);
        ft_quicksort(arr, low, pi - 1);
        ft_quicksort(arr, pi + 1, high);
    }
}

t_hash_table_arr ft_sort_env(t_hash_table* table)
{
	t_hash_table_arr	env_arr;
	
	env_arr = ft_convert_env_to_args(table, EXPORT, 1);
	ft_quicksort(env_arr.table, 0, env_arr.size - 1);
	return (env_arr);
}


t_entity_table *ft_init_entity_table(size_t initialCapacity, t_hash_type type)
{
	size_t			i;
    t_entity_table	*table;

	table = (t_entity_table*)malloc(sizeof(t_entity_table));
    table->size = 0;
    table->capacity = initialCapacity;
    if (!initialCapacity)
	    table->entity = NULL;
    else
	{
		i = 0;
		table->entity = malloc(initialCapacity * sizeof(t_hash_entity_list));
		while (i < initialCapacity)
			ft_init_entity_list(&table->entity[i++]);
	}
    table->type = type;
    return (table);
}

t_hash_table *ft_init_hash_table(size_t initialCapacity, t_hash_type type)
{
	t_hash_table* table;

	table = malloc(sizeof(t_hash_table));
	table->table = ft_init_entity_table(initialCapacity, type);
	return table;
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

t_env_entity	*ft_create_env_entity(t_hash_data data)
{
	t_env_entity	*node;

	node			= (t_env_entity *)malloc(sizeof(t_env_entity));
	node->base.key	= ft_strdup(data.key);
	if ((char*)data.data)
		node->value		= ft_strdup((char *)data.data);
	else
		node->value = NULL;
	node->visibility = data.type;
	node->base.next	= NULL;
	return (node);
}


void	ft_push_entity(t_hash_entity_list *lst, t_hash_data data, t_hash_type type)
{
	t_hash_entity	*node;

    if (type == FUNCTION)
		node = ft_function_to_entity(ft_create_function_entity(data.key, data.data));
    else
		node = ft_env_to_entity(ft_create_env_entity(data));

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
	size_t				i;
	t_hash_entity		*node;
    t_entity_table		*hash_table;
	t_hash_data			data;
	size_t				index;

    i = 0;
	data.type = 0;
    hash_table = ft_init_entity_table(new_capacity, table->table->type);
    while (i < table->table->capacity)
    {
        node = table->table->entity[i].head;
        while (node)
        {
            data.key = node->key;
            if (table->table->type == FUNCTION)
				data.data = ft_entity_to_function(node)->function;
            else
			{
				data.data = ft_entity_to_env(node)->value;
				data.type =  ft_entity_to_env(node)->visibility;
			}
			index = ft_hash_entity(new_capacity, data.key);
            ft_push_entity(&hash_table->entity[index], data, table->table->type);
            node = node->next;
			++hash_table->size;
        }
        ++i;
    }
	ft_free_hash_table(table);
	table->table = hash_table;
	// *table = hash_table;
}

void	ft_insert_entity(t_hash_table *table, t_hash_data data)
{
	size_t index;
	size_t newCapacity;

    if (!table)
        return ;
    if (table->table->size >= table->table->capacity)
	{
		if (!table->table->capacity)
			newCapacity = 10;
        else
            newCapacity = table->table->capacity * 2;
        ft_resize_entity(table, newCapacity);
    }

    index = ft_hash_entity(table->table->capacity, data.key);
	ft_push_entity(&table->table->entity[index], data, table->table->type);
    ++table->table->size;
}

t_function_callback	ft_get_function(t_hash_table *table, char *key)
{
    size_t			index;
	t_hash_entity	*entry;

	if (!key || !*key)
		return NULL;

	index = ft_hash_entity(table->table->capacity, key);
    entry = table->table->entity[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return (ft_entity_to_function(entry)->function);
        entry = entry->next;
    }
    return (NULL);
}


t_function_entity	*ft_get_function_entity(t_hash_table *table, char *key)
{
    size_t			index;
	t_hash_entity	*entry;

	if (!key || !*key)
		return NULL;
	index = ft_hash_entity(table->table->capacity, key);
    entry = table->table->entity[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return (ft_entity_to_function(entry));
        entry = entry->next;
    }
    return (NULL);
}



t_env_entity	*ft_get_env_entity(t_hash_table *table, char *key)
{
    size_t			index;
	t_hash_entity	*entry;

	if (!key || !*key)
		return NULL;
	index = ft_hash_entity(table->table->capacity, key);
    entry = table->table->entity[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return (ft_entity_to_env(entry));
        entry = entry->next;
    }
    return (NULL);
}

char* ft_get_env(t_hash_table *table, char *key)
{
    size_t			index;
    t_hash_entity	*entry;

	if (!key || !*key)
		return NULL;
	index = ft_hash_entity(table->table->capacity, key);
	entry = table->table->entity[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, key))
            return (ft_entity_to_env(entry)->value);
        entry = entry->next;
    }
    return (NULL);
}


void	ft_set_env(t_hash_table *table, t_hash_data data)
{
    size_t			index;
    t_hash_entity	*entry;
	t_env_entity	*ent_tmp;

	if (!data.key || !*data.key)
		return ;
	index = ft_hash_entity(table->table->capacity, data.key);
	entry = table->table->entity[index].head;
    while (entry != NULL)
	{
        if (!ft_strcmp(entry->key, data.key))
        {
			ent_tmp = ft_entity_to_env(entry);
			free(ent_tmp->value);
			if (data.data)
				ent_tmp->value = ft_strdup(data.data);
			else
				ent_tmp->value = NULL;
			ent_tmp->visibility = data.type;
			return ;
		}
        entry = entry->next;
    }
	ft_insert_entity(table, data);
}


void	print_env(t_hash_table* env, t_visibility_type visibility)
{
    size_t 			i;
	t_hash_entity 	*entry;
	t_env_entity	*node;

	i = 0;
    while(i < env->table->capacity)
    {

        entry = env->table->entity[i].head;
        while (entry != NULL)
        {
            node	= ft_entity_to_env(entry);
			if (node->visibility == visibility || node->visibility == NORMAL)
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
	t_hash_data		data;
	char			*assign;

	i = 0;
	table = ft_init_hash_table(10, ENV);
	while (env && env[i])
	{
		assign = ft_strchr(env[i], '=');
		if (assign)
		{
			len = assign - env[i];
			data.data = assign + 1;
		}
		else
		{
			len = ft_strlen(env[i]);
			data.data = NULL;
		}
		data.key = ft_substr(env[i], 0, len);
		if (!ft_strcmp(data.key, "_"))
		{
			data.type = VENV;
			ft_insert_entity(table, data);
		}
		else
		{
			data.type = NORMAL;
			ft_insert_entity(table, data);
		}
		free(data.key);
		++i;
	}
	return (table);
}

t_hash_table* ft_create_func_table()
{
	t_hash_table* funcs;

	funcs = ft_init_hash_table(7, FUNCTION);
	
	ft_insert_entity(funcs, (t_hash_data){ "exit",		ft_exit,	0});
	ft_insert_entity(funcs, (t_hash_data){ "cd",		ft_cd,		0});
	ft_insert_entity(funcs, (t_hash_data){ "echo",		ft_echo,	0});
	ft_insert_entity(funcs, (t_hash_data){ "env",		ft_env,		0});
	ft_insert_entity(funcs, (t_hash_data){ "export",	ft_export,	0});
	ft_insert_entity(funcs, (t_hash_data){ "unset",		ft_unset,	0});
	ft_insert_entity(funcs, (t_hash_data){ "pwd",		ft_pwd,		0});
	return funcs;
}

void	ft_pop_entity(t_hash_table *table, char *key)
{
	size_t				index;
	t_hash_entity		*node;
	t_hash_entity		*tmp;
	t_hash_entity_list	*lst;
	t_hash_entity		*entry;

	if (!table)
		return;
	if (ft_get_env_entity(table, key)->visibility == HIDDEN)
		return ;
	index = ft_hash_entity(table->table->capacity, key);

	lst = &table->table->entity[index];
	
	if (!lst || !lst->head)
		return ;
	if (!ft_strcmp(lst->head->key, key))
	{
		free(lst->head->key);
		if (table->table->type == ENV)
		{
			free(ft_entity_to_env(lst->head)->value);
			free(ft_entity_to_env(lst->head));
		}
		else
			free(ft_entity_to_function(lst->head));
		lst->head = NULL;
		lst->tail = NULL;
	}
	else
	{
		entry = lst->head;
		node = lst->head;
		while (entry)
		{
			if (!ft_strcmp(entry->key, key))
				break;
			node = entry;
			entry = entry->next;
		}
		if (entry && !ft_strcmp(entry->key, key))
		{
			tmp = entry;
			node->next = tmp->next;
			if (tmp == lst->tail)
				lst->tail = node;
			free(tmp->key);
			if (table->table->type == ENV)
			{
				free(ft_entity_to_env(tmp)->value);
				free(ft_entity_to_env(tmp));
			}
			else
				free(ft_entity_to_function(tmp));
		}
	}
	--lst->size;
}



t_hash_table_arr ft_convert_env_to_args(t_hash_table* env, t_visibility_type visibility, int mode)
{
	t_hash_table_arr	arr;
	size_t 				i;
	size_t				j;
	t_hash_entity 		*entry;
	t_env_entity		*node;

	i = 0;
	j = 0;

	arr.table = ft_calloc(env->table->size + 1, sizeof(char*));
    while(i < env->table->capacity)
    {

        entry = env->table->entity[i].head;
        while (entry != NULL)
        {
            node	= ft_entity_to_env(entry);
			if (node->visibility == visibility || node->visibility == NORMAL)
			{
				arr.table[j] = ft_strdup(node->base.key);
				if (node->value)
				{
					arr.table[j] = ft_gnl_strjoin(arr.table[j], "=");
					if (mode)
						arr.table[j] = ft_gnl_strjoin(arr.table[j], "\"");
					arr.table[j] = ft_gnl_strjoin(arr.table[j], node->value);
					if (mode)
						arr.table[j] = ft_gnl_strjoin(arr.table[j], "\"");
				}
				++j;
			}
            entry	= entry->next;
        }
        ++i;
    }
	arr.size = j;
	return arr;
}

void ft_free_hash_table(t_hash_table* table)
{
	size_t 			i;
	t_hash_entity 	*entry;
	t_hash_entity	*entity;

	if (!table)
		return;
	i = 0;
    while(i < table->table->capacity)
    {

        entry = table->table->entity[i].head;
        while (entry != NULL)
        {
			entity = entry->next;
			free(entry->key);
			if (table->table->type == ENV)
			{
				free(ft_entity_to_env(entry)->value);
				free(ft_entity_to_env(entry));
			}
			else
				free(ft_entity_to_function(entry));
            entry = entity;
        }
        ++i;
    }
	free(table->table->entity);
	free(table->table);
	table->table = NULL;
}


void                print_env_table(t_hash_table_arr arr)
{
	size_t i = 0;
	while (arr.table && arr.table[i])
	{
		ft_putstr_fd("declare -X ", STDOUT_FILENO);
		ft_putstr_fd(arr.table[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		++i;
	}
	
}

void ft_clear_hash_table(t_hash_table* table)
{
	free(table);
}

