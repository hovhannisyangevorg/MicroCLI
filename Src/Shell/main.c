/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/12/23 21:10:15 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		list = ft_multi_split(line, SEPARARTORS, 0);
		if (list->size != 0){
			ft_ordering(list);
		}
		// ft_push_front(list, 0, ft_strdup("START"));
		ft_split_token(list);
		// ft_push_back(list, 0, ft_strdup("END"));
		ft_print_list(*list);
		
		ft_parser(list);
		ft_free_list(list);
		free(line);
    }
    clear_history();
}

// int	ft_find_close(char* str, size_t size, int openIndex)
// {
// 	int count;
// 	size_t i;

// 	i = openIndex + 1;
// 	count = 1;
// 	while (i < size)
// 	{
// 		if (str[i] == '(')
// 			++count;
// 		else if (str[i] == ')')
// 		{
// 			--count;
// 			if (0 == count)
// 				return (i);
// 		}
// 		++i;
// 	}
// 	return (-1);
// }

// int ft_find(char* str, char c, size_t pos)
// {
// 	size_t i = pos;
// 	while(str[i])
// 	{
// 		if (str[i] == c)
// 			return i;
// 		++i;
// 	}
// 	return -1;
// }

// char* get_sub_string(char *str, size_t size, size_t start)
// {
	
// 	size_t pos = ft_find(str, '(', start);
// 	if ((int)pos < 0)
// 		return NULL;
// 	size_t end = ft_find_close(str, size, pos);
// 	// printf("%lu\n", (end - start - 1));
// 	return (ft_substr(str, pos + 1, end - start - 2));
// }



// t_ast_node* correct_subshell(t_ast_node* root)
// {
// 	if (root->token_type == TEXT)
// 	{
// 		if (ft_strchr(root->token, OPBREK) || ft_strchr(root->token, CLBREK))
// 		{
// 			char* subshell = get_sub_string(root->token, ft_strlen(root->token), 0);
// 			t_list_token* list = ft_multi_split(subshell, SEPARARTORS, 0);
// 			if (list->size != 0){
// 				ft_ordering(list);
// 			}
// 				// ft_push_front(list, 0, ft_strdup("START"));
// 			// ft_print_list(*list);
// 			ft_split_token(list);
// 			t_global_tree* tree = ft_shunting_yard_build_ast(list);
// 			ft_push_shant_stack(root->subshell, tree->ast_node);
// 			// correct_subshell(tree->ast_node);
// 		}
// 	}
// 	return root;
// }


// int main()
// {
// 	char* str = "((ls) | (grep) | e | r | k)";
// 	char* subshell = get_sub_string(str, ft_strlen(str), 0);
// 	t_list_token* list = ft_multi_split(subshell, SEPARARTORS, 0);
// 	if (list->size != 0){
// 		ft_ordering(list);
// 	}
// 		// ft_push_front(list, 0, ft_strdup("START"));
// 	// ft_print_list(*list);
// 	ft_split_token(list);
// 	t_global_tree* tree = ft_shunting_yard_build_ast(list);
// 	// ft_push_shant_stack(root->subshell, tree->ast_node);
// 	// correct_subshell(tree->ast_node);
// 	// char* out = ;
// 	// printf("%s\n", out);
	
// 	ft_ast_print(tree->ast_node, ft_strdup(""), 0, 1);
	
// 	// size_t index = 0;
// 	// t_token tok;

// 	// ft_init_token(&tok, SUBSHELL, ft_strdup(str));
// 	// t_ast_node* node = ft_create_ast_node(&tok);
// 	// ft_sub1(node, ft_strlen(str), &index, 0);
// 	// ft_ast_print(node, ft_strdup(""), 0, 1);
// 	// ft_program();
// 	return (0);	
// }



int main()
{
	ft_program();
	return (0);	
}



















































































// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>

// // Forward declaration of Node
// struct Node;

// typedef struct Node {
//     char data;
//     struct Node* next;
// } Node;

// typedef struct {
//     Node* top;
// } Stack;




// void push(Stack* s, char data) {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     newNode->data = data;
//     newNode->next = s->top;
//     s->top = newNode;
// }

// char pop(Stack* s) {
//     if (s->top == NULL) {
//         printf("Stack is empty.\n");
//         return '\0';
//     }
//     char data = s->top->data;
//     Node* temp = s->top;
//     s->top = s->top->next;
//     free(temp);
//     return data;
// }

// int isOperator(char c) {
//     return (c == '+' || c == '-' || c == '*' || c == '/');
// }

// int precedence(char c) {
//     switch(c) {
//         case '+':
//         case '-':
//             return 1;
//         case '*':
//         case '/':
//             return 2;
//         default:
//             return 0;
//     }
// }






// void shuntingYard(const char* infix, char* postfix) 
// {
// 	int i;
// 	int j;
//     Stack operatorStack;

//     i = 0; 
// 	j = 0;
//     operatorStack.top = NULL;


//     while (infix[i]) 
// 	{
//         if (isdigit(infix[i])) 
// 		{
// 			printf("shshhshshshsshhshshshsh\n");
//             postfix[j++] = infix[i++];
//             while (isdigit(infix[i])) {
//                 postfix[j++] = infix[i++];
//             }
//             postfix[j++] = ' ';
//         }
// 		else if (isOperator(infix[i])) 
// 		{
//             while (operatorStack.top && (precedence(infix[i]) <= precedence(operatorStack.top->data))) {
//                 postfix[j++] = pop(&operatorStack);
//                 postfix[j++] = ' ';
//             }
//             push(&operatorStack, infix[i++]);
//         } 
// 		else if (infix[i] == '(') 
// 		{
//             push(&operatorStack, infix[i++]);
//         } 
// 		else if (infix[i] == ')') 
// 		{
//             while (operatorStack.top && operatorStack.top->data != '(') {
//                 postfix[j++] = pop(&operatorStack);
//                 postfix[j++] = ' ';
//             }
//             if (operatorStack.top && operatorStack.top->data == '(') {
//                 pop(&operatorStack);
//             }
//             i++;
//         } else 
// 		{
//             i++;  // skip any other characters
//         }
//     }
    
//     while (operatorStack.top) {
//         postfix[j++] = pop(&operatorStack);
//         postfix[j++] = ' ';
//     }
//     postfix[j] = '\0';  // Null-terminate the string
// }




// int main() {
//     char infix[] = "3 + 4 * 2 / ( 1 - 5 )";
//     char postfix[50];

//     shuntingYard(infix, postfix);

//     printf("Infix: %s\n", infix);
//     printf("Postfix: %s\n", postfix);
//     return 0;
// }





























































































// union test
// {
// 	char 	x;
// 	int 	d;
// 	int 	o;
// 	float 	y;
// };

// static int	ft_find_index(char *expression, int index)
// {
// 	int i;
	
// 	t_stack *stack;
// 	stack = ft_initialize_stack();
// 	// t_stack *stack2;
// 	// stack2 = ft_initialize_stack();
// 	i = 0;
// 	while (expression && expression[i])
// 	{
// 		if (expression[i] == '(')
// 		{
// 			// ft_push_stack(stack, '(');
// 			ft_push_stack(stack, i);
// 		}
// 		else if (expression[i] == ')')
// 		{
// 			if (stack->top)
// 			{
// 				int res = stack->top->data;
// 				printf("%d\n", res);
// 				if (res == index)
// 					return i;
// 			}
// 			ft_pop_stack(stack);
// 			// if (c != '(')
// 			// {
// 			// 	ft_free_stack(stack);
// 			// 	free(stack);
// 			// 	return (0);
// 			// }
// 		}
// 		++i;
	
// 	}
// 	ft_free_stack(stack);
// 	free(stack);
// 	return -1;
// }



// int main()
// {
// 	// char *p = "((dsadasdsa(dsadas)))";
// 	// printf("%d\n", ft_find_index(p, 1));
// 	ft_program();
// 	return (0);	
// }

