/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sematic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:08:20 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/19 13:17:11 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_sematic(t_list_token *list, int isast)
{
	t_global_tree *tree;
	
	if(isast)
	{
		tree = ft_shunting_yard_build_ast(list);
		
		ft_build_subshell(tree->ast_node);
		// printf("%lu\n", tree->ast_node->left->subshell->top->ast_node->subshell->size);
		// ft_sematic_with_tree();
		ft_ast_print(tree->ast_node, ft_strdup(""), 0, 1);
	}
	else
	{
		printf("\n---------------\n\n/**\n * Pipe Validation\n * \n */\n// ft_sematic_with_list(t);\n");
	}
}




































































































// void correct_tree(t_ast_node *tree)
// {
// 	if (!tree)
// 		return ;

// 	if (tree->token_type == TEXT)
// 	{
// 		t_list_token* sub_list = ft_multi_split(tree->token, SUBSHELLSEP, 1);
// 		ft_ordering(sub_list);
// 		// ft_print_list(*sub_list);
// 		if(isbrakets(sub_list))
// 		{
// 			t_global_tree* sub_tree = ft_shunting_yard_build_ast(sub_list);
// 			tree->token_type = SUBSHELL;
// 			tree->left = sub_tree->ast_node;	
// 		}

// 	}
// 	correct_tree(tree->left);
// 	correct_tree(tree->right);
// }