/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:25:50 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/17 22:57:14 by gevorg           ###   ########.fr       */
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

void ft_build_subshell(t_ast_node *tree)
{
	if (!tree)
		return ;
	if (tree->token_type == TEXT)
	{
		if (ft_strchr(tree->token, OPBREK) || ft_strchr(tree->token, CLBREK))
		{
			size_t index = 0;
			ft_subshell(tree, &index);
			
			// t_ast_node* node = tree;
			
			// tree->token_type = SUBSHELL;
			
		}
	}
	ft_build_subshell(tree->left);
	ft_build_subshell(tree->right);
}

void	ft_subshell(t_ast_node* sub, size_t *index)
{
	
	t_token 		token;
	t_ast_node 		*node;
	// t_shant_stack 	*tmp_node;
	char 			*out;
	char 			tmp;
	size_t 			start = 0;
	
	while (*index < ft_strlen(sub->token))
	{
		tmp = sub->token[*index];
		
		if (tmp == '(')
		{
			++(*index);
			ft_subshell(sub, index);
		} else if (tmp == ')')
		{
			++(*index);
			break;
		} else
		{
			start = *index;
			while (start < ft_strlen(sub->token) && sub->token[*index] != '(' && sub->token[*index] != ')')
				++(*index);
			out = ft_substr(sub->token, start, (*index) - start);
			ft_init_token(&token, TEXT, out);
			node = ft_create_ast_node(&token);
			ft_push_shant_stack(sub->subshell, node);
			free(token.token);
		}
		++(*index);
	}
	sub->token_type = SUBSHELL;
	// free(sub->token);
	// sub->token = ft_strdup("SubShell");
	// ft_init_token(&token, SUBSHELL, ft_strdup("SubShell"));
	// node = ft_create_ast_node(&token);
	// tmp_node = sub->subshell->top;
	// while (tmp_node)
	// {
	// 	ft_push_shant_stack(sub->subshell, tmp_node->ast_node);
	// 	tmp_node = tmp_node->next; 
	// }
	// ft_push_shant_stack(sub->subshell, node);
}









































































// void ft_create_subtree(t_ast_node *tree)
// {
// 	if (!tree)
// 		return ;

// 	if (tree->token_type == SUBSHELL)
// 	{
// 		// ft_subtree_TST(tree);
// 	}
	
// 	ft_create_subtree(tree->left);
// 	ft_create_subtree(tree->right);
// }