/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:19:41 by gevorg            #+#    #+#             */
/*   Updated: 2023/09/23 17:10:43 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_panic(char *error);
size_t	ft_strlen(const char *str);


typedef struct	s_stack		t_stack;
typedef struct	s_node		t_node;

struct s_node
{
	char data;
	t_node *next;
};

struct s_stack
{
	t_node *top;
};

t_stack *initialize_stack()
{
	t_stack *stack;
	
	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL)
		return (NULL);
	stack->top = NULL;
	return (stack);
}

int is_empty(t_stack *stack)
{
	return (stack->top == NULL);
}

void	push_stack(t_stack *stack, char item)
{
	t_node *new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return ;
	new_node->data = item;
	new_node->next = stack->top;
	stack->top = new_node;
}

char pop_stack(t_stack *stack)
{
	char item;
	t_node *temp;

	if (is_empty(stack))
		return (0);
	temp = stack->top;
	item = temp->data;
	stack->top = temp->next;
	free(temp);
	return (item);
}

void free_stack(t_stack *stack)
{
	if (stack == NULL || stack->top == NULL)
		return ;
	while (!is_empty(stack))
		pop_stack(stack);
	// free(stack);
	stack = NULL;
}



static int	balancer(char *expression)
{
	int i;
	int balanced;
	
	t_stack *stack = initialize_stack();
	i = 0;
	while (expression && expression[i])
	{
		if (expression[i] == '(')
			push_stack(stack, '(');
		else if (expression[i] == ')')
		{
			if (pop_stack(stack) != '(')
			{
				free_stack(stack);
				free(stack);
				return (0);
			}
		}
		i++;
	}
	balanced = is_empty(stack);
	free_stack(stack);
	free(stack);
	return (balanced);
}

void is_balanc(char *expression)
{
	if (!balancer(expression))
		ft_panic("MiniShell Oops: Syntax error rarentheses are not balanced  `('");
	
}



int main()
{
	char expression[] = "((((((((((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))))))))))";

	is_balanc(expression);

	return (0);
}





































































void	ft_panic(char *error)
{
	write (2, error, ft_strlen(error));
	write (2, "\n", 1);
	exit (1);
}

size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (ptr && *ptr)
		ptr++;
	return (ptr - str);
}
