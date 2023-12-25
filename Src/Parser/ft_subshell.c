/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:25:50 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/25 21:40:13 by gevorg           ###   ########.fr       */
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

// Preorder traversal
void ft_build_subshell(t_ast_node *ast_node)
{
	t_shant_stack* node;

	if (!ast_node)
		return ;

	if (ast_node->token_type == TEXT)
	{
		if (ft_strchr(ast_node->token, OPBREK) || ft_strchr(ast_node->token, CLBREK))
		{
			ft_correct_subshell(ast_node);
			free(ast_node->token);
			ast_node->token = ft_strdup("SubShell");
		}
	}
	node = ast_node->subshell->top;
	while (node)
	{
		ft_build_subshell(node->ast_node);
		node = node->next;
	}
	
	ft_build_subshell(ast_node->left);
	ft_build_subshell(ast_node->right);
}

void ft_subshell_hier(t_ast_node* root)
{
	if (!root)
		return;
	t_shant_stack* node = root->subshell->top;
	while (node)
	{
		ft_correct_subshell(node->ast_node);
		node = node->next;
	}
	ft_correct_subshell(root->left);
	ft_correct_subshell(root->right);
	
}


t_ast_node* ft_correct_subshell(t_ast_node* root)
{
	t_global_tree	*tree;
	t_list_token	*list;
	char			*subshell;

	if (!root)
		return root;

	if (root->token_type == TEXT)
	{
		if (ft_strchr(root->token, OPBREK) || ft_strchr(root->token, CLBREK))
		{
			size_t start = 0;
			while (1)
			{
				subshell = get_sub_string(root->token, ft_strlen(root->token), &start);
				if (subshell)
				{
					list = ft_multi_split(subshell, SEPARARTORS, 0);
					if (list->size != 0)
						ft_ordering(list);
					ft_split_token(list);
					tree = ft_shunting_yard_build_ast(list);
					tree->ast_node->parent = root;
					ft_push_shant_stack(root->subshell, tree->ast_node);

					ft_subshell_hier(tree->ast_node);
				}
				else
					break ;
			}
		}
	}
	return (root);
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

int ft_find(char* str, char c, size_t pos, size_t size)
{
	size_t i;
	
	i = pos;
	if (pos > size)
		return -1;
	while(str && str[i])
	{
		if (str[i] == c)
			return i;
		++i;
	}
	return (-1);
}

char* get_sub_string(char *str, size_t size, size_t* start)
{
	size_t pos;
	size_t end;
	
	pos = ft_find(str, '(', *start, size);
	if ((int)pos < 0)
		return NULL;
	end = ft_find_close(str, size, pos);
	if ((int)end < 0)
		return (NULL);
	*start = end + 1;
	return (ft_substr(str, pos + 1, end - pos - 1));
}
