/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:25:50 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/23 21:41:16 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	isbrakets(t_list_token *list)
{
	t_token *tmp;

	tmp = list->head;

	while (tmp)
	{
		if (tmp->type == OPBREK || tmp->type == CLBREK)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void ft_build_subshell(t_ast_node *ast_node)
{
	// size_t index;

	if (!ast_node)
		return ;

	if (ast_node->token_type == TEXT)
	{
		if (ft_strchr(ast_node->token, OPBREK) || ft_strchr(ast_node->token, CLBREK))
		{
			ft_correct_subshell(ast_node);
			free(ast_node->token);
			ast_node->token = ft_strdup("SubShell");
			// index = 0;
			// ft_subshell(ast_node, &index);
		}
	}
	t_shant_stack* node = ast_node->subshell->top;
	while (node)
	{
		ft_build_subshell(node->ast_node);
		node = node->next;
	}
	
	ft_build_subshell(ast_node->left);
	ft_build_subshell(ast_node->right);
}

int	ft_find_close(char* str, size_t size, int openIndex)
{
	int count;
	size_t i;

	i = openIndex + 1;
	count = 1;
	while (i < size)
	{
		if (str[i] == '(')
			++count;
		else if (str[i] == ')')
		{
			--count;
			if (0 == count)
				return (i);
		}
		++i;
	}
	return (-1);
}

int ft_find(char* str, char c, size_t pos)
{
	size_t i = pos;
	while(str[i])
	{
		if (str[i] == c)
			return i;
		++i;
	}
	return -1;
}

char* get_sub_string(char *str, size_t size, size_t start)
{
	
	size_t pos = ft_find(str, '(', start);
	if ((int)pos < 0)
		return NULL;
	size_t end = ft_find_close(str, size, pos);
	if ((int)end < 0)
		return (NULL);
	--end;
	printf("end = %lu\nstart = %lu\n", end , pos);
	return (ft_substr(str, pos + 1, end - pos - 1));
}



t_ast_node* ft_correct_subshell(t_ast_node* root)
{
	if (!root)
		return root;
	if (root->token_type == TEXT)
	{
		if (ft_strchr(root->token, OPBREK) || ft_strchr(root->token, CLBREK))
		{
			char* subshell = get_sub_string(root->token, ft_strlen(root->token), 0);
			if (subshell)
			{
				t_list_token* list = ft_multi_split(subshell, SEPARARTORS, 0);
				if (list->size != 0){
					ft_ordering(list);
				}
					// ft_push_front(list, 0, ft_strdup("START"));
				// ft_print_list(*list);
				ft_split_token(list);
				t_global_tree* tree = ft_shunting_yard_build_ast(list);
				ft_push_shant_stack(root->subshell, tree->ast_node);
				ft_correct_subshell(tree->ast_node);
				
			}
		}
	}
	return root;
}






























































