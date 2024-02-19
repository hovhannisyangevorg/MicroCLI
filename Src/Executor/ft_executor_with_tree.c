/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_with_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:53:59 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 18:04:36 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	ft_pipe_count_tree(t_ast_node *tree)
{
	size_t count_left;
	size_t count_right;
	
	
	count_right	= 0;
	count_left	= 0;
	if (!tree)
		return (0);
	if (tree->token_type == PIPE)
	{
		count_left	= ft_pipe_count_tree(tree->left);
		count_right	= ft_pipe_count_tree(tree->right);
		return (count_left + count_right + 1);
	}
	count_left 	= ft_pipe_count_tree(tree->left);
	count_right = ft_pipe_count_tree(tree->right);
	return (count_left + count_right);
}

