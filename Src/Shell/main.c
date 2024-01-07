/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2024/01/03 21:42:05 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stddef.h>

void	ft_program()
{
	char 			*line;
	t_list_token	*list;

	signal(SIGINT, sig_handler_c);
	rl_catch_signals = 0;
	while (1)
	{
		line = ft_get_line();
		if (!line)
			return ;
		ft_brackets_balanced(line);
        list = ft_tokenize(line, SEPARATORS);
		ft_print_list(list->head);
		ft_parser(list);
		ft_free_list(list);
		free(line);
    }
    clear_history();
}


void f()
{
	printf("%d\n", 6);
}

void f1()
{
	printf("%f\n", 8.2);
}

// void print_env1(t_hash_table* env, char** args)
// {
//     printf("%lu\n", env->size);
//     size_t i = 0;
//     while(args && args[i])
//     {
// 		char* assign = ft_strchr(args[i], '=');
// 		size_t len;
// 		if (assign)
// 		{
// 			len = assign - args[i];
// 		}
// 		else
// 		{
// 			len = ft_strlen(args[i]);
// 		}
// 		char *key = ft_substr(args[i], 0, len);
//         char* str = ft_get_env(env, key);
// 		printf("%s=%s\n", key, str);
//         ++i;
//     }
// }
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


// Function to print the elements in sorted order
void printSortedKey(t_hash_table *hashTable) {
    // Iterate through the hash table and collect elements in an array
    t_env_entity *sortedArray[hashTable->capacity];
    int index = 0;

    for (size_t i = 0; i < hashTable->capacity; ++i) {
        t_hash_entity *current = hashTable->table[i].head;
        while (current != NULL) {
            sortedArray[index++] = ft_entity_to_env(current);
            current = current->next;
        }
    }

    // Sort the array based on keys (you may use any sorting algorithm)
    // For simplicity, we use a basic bubble sort here.
    for (int i = 0; i < index - 1; ++i) {
        for (int j = 0; j < index - i - 1; ++j) {
            if (ft_strcmp(sortedArray[j]->base.key, sortedArray[j + 1]->base.key) > 0) {
                // Swap elements
                t_env_entity *temp = sortedArray[j];
                sortedArray[j] = sortedArray[j + 1];
                sortedArray[j + 1] = temp;
            }
        }
    }

    // Print the sorted elements
    for (int i = 0; i < index; ++i) {
        printf("%s=%s\n", sortedArray[i]->base.key, sortedArray[i]->value);
    }
}

void printSortedValue(t_hash_table *hashTable) {
    // Iterate through the hash table and collect elements in an array
    t_env_entity *sortedArray[hashTable->capacity];
    int index = 0;

    for (size_t i = 0; i < hashTable->capacity; ++i) {
        t_hash_entity *current = hashTable->table[i].head;
        while (current != NULL) {
            sortedArray[index++] = ft_entity_to_env(current);
            current = current->next;
        }
    }

    // Sort the array based on keys (you may use any sorting algorithm)
    // For simplicity, we use a basic bubble sort here.
    for (int i = 0; i < index - 1; ++i) {
        for (int j = 0; j < index - i - 1; ++j) {
            if (ft_strcmp(sortedArray[j]->value, sortedArray[j + 1]->value) > 0) {
                // Swap elements
                t_env_entity *temp = sortedArray[j];
                sortedArray[j] = sortedArray[j + 1];
                sortedArray[j + 1] = temp;
            }
        }
    }

    // Print the sorted elements
    for (int i = 0; i < index; ++i) {
        printf("%s=%s\n", sortedArray[i]->base.key, sortedArray[i]->value);
    }
}

// composition 
int main(int ac, char** av, char** env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_hash_table* table;

	table = ft_init_hash_table(0, ENV);

	table = ft_create_env(env);
	(void)table;
	// print_env(table);
	// printf("%d\n", ft_get_env(table, "SHELL") == 0);
	// size_t i = 0;
	// while (env && env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	++i;
	// }
	// table = ft_init_hash_table(0, ENV);
	// ft_insert_entity(table, "01", "fff");
	// ft_insert_entity(table, "a", "bbb");
	// print_env(table);
	// ft_insert_entity(table, "SHELL", "/bin/bash");
	// ft_insert_entity(table, "SESSION_MANAGER", "local/hohayrap-GF63-Thin-11UD:@/tmp/.ICE-unix/1898,unix/hohayrap-GF63-Thin-11UD:/tmp/.ICE-unix/1898");
	// ft_insert_entity(table, "XDG_CONFIG_DIRS", "/etc/xdg/xdg-gnome:/etc/xdg");
	// ft_insert_entity(table, "GNOME_DESKTOP_SESSION_ID", "this-is-deprecated");
	// ft_insert_entity(table, "SSH_AUTH_SOCK", "/run/user/1000/keyring/ssh");
	// char* call = ft_get_env(table, "f");
	// if (!call)
	// printf("%d\n", table->table[0].head == 0);
	// printf("1: %s\n", ft_get_env(table, "PWD"));
	// print_env(table);
	printSortedKey(table);
	// 	printf("no such function\n");
	// else
	// 	printf("%s\n", call);
		// call();
	// printf("%lu\n", sizeof(t_shape));
	// t_rect r;
	// r.x = 8;
	// // r.y = 9;
	// t_shape* s = (t_shape* )&r;

	// printf("%d\n", s->x);
	
	// ft_program();
	return (0);	
}

































// #include <stdio.h>
// #include <string.h>

// char	*strtok_custom(char *str, const char *delim)
// {
// 	char 			*start;
//     static char 	*next_token = NULL;
	
// 	if (!str && !next_token)
// 		return (NULL);
// 	if (str)			//
// 		next_token = str;
// 	while (*next_token && strchr(delim, *next_token))
//         ++next_token;
// 	if (!*next_token) {
//         next_token = NULL;
//         return NULL;
//     }

//     start = next_token;
//     while (*next_token && !strchr(delim, *next_token))
// 		++next_token;
	
//     if (*next_token) {
//         *next_token = '\0';
//         ++next_token;
//     } else
// 		next_token = NULL;

//     return (start);
// }

// int main() {
//     char str[] = "Hello,Armeina,atatt,,,,,";
//     const char delim[] = ",";
//     char *token;

//     token = strtok_custom(str, delim);
	
// 	printf("%s\n", token);
//     while (token != NULL) {
//         printf("%s\n", token);
//         token = strtok_custom(NULL, delim);
//     }

//     return 0;
// }












