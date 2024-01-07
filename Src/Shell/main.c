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
	t_container		*cont;

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
		cont = ft_parser(list);
		ft_executor(cont);
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



// Function to print the elements in sorted order
// void printSortedKey(t_hash_table *hashTable) {
//     // Iterate through the hash table and collect elements in an array
//     t_env_entity *sortedArray[hashTable->capacity];
//     int index = 0;

//     for (size_t i = 0; i < hashTable->capacity; ++i) {
//         t_hash_entity *current = hashTable->table[i].head;
//         while (current != NULL) {
//             sortedArray[index++] = ft_entity_to_env(current);
//             current = current->next;
//         }
//     }

//     // Sort the array based on keys (you may use any sorting algorithm)
//     // For simplicity, we use a basic bubble sort here.
//     for (int i = 0; i < index - 1; ++i) {
//         for (int j = 0; j < index - i - 1; ++j) {
//             if (ft_strcmp(sortedArray[j]->base.key, sortedArray[j + 1]->base.key) > 0) {
//                 // Swap elements
//                 t_env_entity *temp = sortedArray[j];
//                 sortedArray[j] = sortedArray[j + 1];
//                 sortedArray[j + 1] = temp;
//             }
//         }
//     }

//     // Print the sorted elements
//     for (int i = 0; i < index; ++i) {
//         printf("%s=%s\n", sortedArray[i]->base.key, sortedArray[i]->value);
//     }
// }

// void printSortedValue(t_hash_table *hashTable) {
//     // Iterate through the hash table and collect elements in an array
//     t_env_entity *sortedArray[hashTable->capacity];
//     int index = 0;

//     for (size_t i = 0; i < hashTable->capacity; ++i) {
//         t_hash_entity *current = hashTable->table[i].head;
//         while (current != NULL) {
//             sortedArray[index++] = ft_entity_to_env(current);
//             current = current->next;
//         }
//     }

//     // Sort the array based on keys (you may use any sorting algorithm)
//     // For simplicity, we use a basic bubble sort here.
//     for (int i = 0; i < index - 1; ++i) {
//         for (int j = 0; j < index - i - 1; ++j) {
//             if (ft_strcmp(sortedArray[j]->value, sortedArray[j + 1]->value) > 0) {
//                 // Swap elements
//                 t_env_entity *temp = sortedArray[j];
//                 sortedArray[j] = sortedArray[j + 1];
//                 sortedArray[j + 1] = temp;
//             }
//         }
//     }

//     // Print the sorted elements
//     for (int i = 0; i < index; ++i) {
//         printf("%s=%s\n", sortedArray[i]->base.key, sortedArray[i]->value);
//     }
// }

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
	ft_program();
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












