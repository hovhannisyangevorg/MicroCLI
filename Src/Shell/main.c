/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/12/25 21:40:40 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stddef.h>



// void	ft_program()
// {
// 	char 			*line;
// 	t_list_token	*list;

// 	signal(SIGINT, sig_handler_c);
// 	rl_catch_signals = 0;
// 	while (1)
// 	{
// 		line = ft_get_line();
// 		if (!line)
// 			return ;
// 		ft_brackets_balanced(line);
// 		list = ft_multi_split(line, OPERATORS, 0);
// 		if (list->size != 0){
// 			ft_ordering(list);
// 		}
// 		// ft_push_front(list, 0, ft_strdup("START"));
// 		ft_split_token(list);
// 		// ft_push_back(list, 0, ft_strdup("END"));
// 		ft_print_list(*list);
		
// 		ft_parser(list);
// 		ft_free_list(list);
// 		free(line);
//     }
//     clear_history();
// }


// case         (()()()()()()()()()()()()()()()()()()()()()()()()()()()()) | (()()()()()()()()()()()())




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
		// ft_print_list(list->head);
		ft_parser(list);
		ft_free_list(list);
		free(line);
    }
    clear_history();
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Define a function pointer type for the functions that will be stored in the hash table
// typedef void (*FunctionPtr)();

// // Define a structure for each entry in the hash table
// typedef struct HashTableEntry {
//     char* key;
//     FunctionPtr function;
//     struct HashTableEntry* next;
// } HashTableEntry;

// // Define the hash table itself
// typedef struct {
//     HashTableEntry** entries;
//     size_t size;
//     size_t capacity;
// } HashTable;

// // Initialize the hash table
// HashTable* initializeHashTable(int initial) {
//     HashTable* table = (HashTable*)malloc(sizeof(HashTable));
//     table->entries = (HashTableEntry**)calloc(initial, sizeof(HashTableEntry*));
//     table->size = 0;
//     table->capacity = initial;
//     return table;
// }

// // Hash function to determine the index in the hash table
// size_t hash(char* key, size_t capacity)
// {
//     size_t hashValue = 0;
//     while (*key)
//     {
//         hashValue += *key;
//         ++key;
//     }
//     return hashValue % capacity;
// }

// void insertFunction(t_function_table* table, char* key, t_function_callback function) {
//     t_function_entity** new_entity;
//     if (table->size >= (table->capacity * 2) / 3) {
//         size_t newCapacity = table->capacity * 2;
//         new_entity = malloc(newCapacity * sizeof(t_function_entity*));
//         size_t i = 0;
//         while (i < table->size)
//         {
//             new_entity[i] = table->entries[i];
//             ++i;
//         }
//         ft_memset(table->entries + table->capacity, 0, (newCapacity - table->capacity) * sizeof(HashTableEntry*));
//         table->capacity = newCapacity;
//     }

//     size_t index = hash(key, table->capacity);

//     // Create a new entry
//     HashTableEntry* newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry));
//     newEntry->key = strdup(key);
//     newEntry->function = function;
//     newEntry->next = table->entries[index];

//     // Update the head of the linked list for the corresponding hash index
//     table->entries[index] = newEntry;
//     table->size++;
// }

// // Retrieve a function from the hash table
// FunctionPtr getFunction(HashTable* table, char* key) {
//     size_t index = hash(key, table->capacity);

//     // Search for the entry with the given key
//     HashTableEntry* entry = table->entries[index];
//     while (entry != NULL) {
//         if (strcmp(entry->key, key) == 0) {
//             return entry->function;
//         }
//         entry = entry->next;
//     }

//     return NULL; // Function not found
// }

// // Example functions to be stored in the hash table
// void function1(int x) {
//     printf("Function 1 %d\n", x);
// }

// void function2() {
//     printf("Function 2\n");
// }

// void function3() {
//     printf("Function 3\n");
// }

// int main() {
//     HashTable* functionTable = initializeHashTable();

//     // Insert functions into the hash table
//     insertFunction(functionTable, "func1", &function1);
//     insertFunction(functionTable, "func2", &function2);
//     insertFunction(functionTable, "func3", &function3);

//     // Use the functions retrieved from the hash table
//     FunctionPtr func = getFunction(functionTable, "func1");
//     if (func != NULL) {
//         func();
//     }

//     func = getFunction(functionTable, "func2");
//     if (func != NULL) {
//         func();
//     }

//     func = getFunction(functionTable, "func3");
//     if (func != NULL) {
//         func();
//     }

//     // Free allocated memory
//     // ...

//     return 0;
// }


// int main() {
//     // Example input string
//     // char original[] = "(ls (hh))";

//     // // Allocate memory for a copy of the string
//     // char *copy = malloc(strlen(original) + 1);
//     // if (copy == NULL) {
//     //     perror("Memory allocation failed");
//     //     return 1;
//     // }

//     // // Copy the original string to the allocated memory
//     // strcpy(copy, original);

//     // // // Tokenize the copy and print each token
//     // t_list_token* lst = tokenizeString(copy, SEPARATORS);
//     // ft_print_list(*lst);
// 	// t_token* 	tok = ft_find_close_list(lst->head->next->next);
//     // printf("%d\n", tok == 0);
	
//     // ft_parser(lst);
//     // categorize(lst);
//     // correct_list(lst);

//     // Free the dynamically allocated memory
//     // free(copy);
//     ft_program();

//     return 0;
// }
int main()
{
	
	// t_token t;
	// ft_init_token(&t, TEXT, "(ls | (grep) (hi))");
	// t_ast_node* node = ft_create_ast_node(&t);
	// node = ft_correct_subshell(node);
	// ft_ast_print(node, ft_strdup(""), 0, 1);
	// fixaca
	// myus casenel jogaca hopar
	// ft_substr("(()()()()()()()()()()()()()()()()()()()()()()()()()()()())")
	ft_program();
	return (0);	
}














