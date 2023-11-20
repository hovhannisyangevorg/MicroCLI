/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sematic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:08:20 by gevorg            #+#    #+#             */
/*   Updated: 2023/11/20 22:27:58 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_sematic(t_list_token *list, int isast)
{
	t_global_tree *tree;
	
	if(isast)
	{
		tree = ft_sematic_with_tree(list);
		ft_ast_print(tree->ast_node, ft_strdup(""), 0, 1);
	}
	// else
	// {
	// 	/**
	// 	 * piperi 	validacia 
	// 	 * piperic 	heto arjeqner linen 
	// 	 * 
	// 	 */
	// 	// ft_sematic_with_list(t);
	// }
	
}



t_global_tree	*ft_sematic_with_tree(t_list_token *list)
{
	t_global_tree *tree;

	tree = ft_shunting_yard_build_ast(list);
	return (tree);	
}