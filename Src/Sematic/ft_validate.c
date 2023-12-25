/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:41:20 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/25 19:52:29 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_ast_node* ft_ast_left(t_ast_node* root)
{
	
	while (root && root->left)
	{
		root = root->left;
	}
	return root;
}

t_ast_node* ft_ast_right(t_ast_node* root)
{
	
	while (root && root->right)
	{
		root = root->right;
	}
	return root;
}

// int ft_validate_left(t_ast_node *ast_node)
// {
// 	t_ast_node* left;

// 	left = ft_ast_left(ast_node);
// 	if (left && left->parent && !left->parent->right)
// 		return -1;
// 	while (left->parent)
// 	{
		
// 		left = left->parent;
// 	}
// }

// int ft_validate_right(t_ast_node* ast_node)
// {
// 	t_ast_node* left;
// 	t_ast_node* right;

// 	left = ft_ast_left(ast_node);
// 	if (right && left->parent && !left->parent->right)
// 		return -1;
// 	ft_validate_left(left->parent);
// }

// int ft_validate(t_ast_node *ast_node)
// {
// 	if (!ast_node)
// 		return;
	
// 	right = ft_ast_right(ast_node);
// 	if (right && right->parent && !right->parent->left)
// 		return -1;

	
	
// 	// t_shant_stack* node;

// 	// if (!ast_node)
// 	// 	return ;

	

// 	// node = ast_node->subshell->top;
// 	// while (node)
// 	// {
		
// 	// 	node = node->next;
// 	// }
	
// 	// ft_build_subshell(ast_node->left);
// 	// ft_build_subshell(ast_node->right);
// }