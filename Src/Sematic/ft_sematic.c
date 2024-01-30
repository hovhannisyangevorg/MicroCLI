/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sematic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:08:20 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/29 17:14:15 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_global_tree *ft_sematic(t_list_token *list, int isast)
{
	t_global_tree 	*tree;
	t_token 		root;
	t_status_codes	status;
	char			*str;

	tree = NULL;
	if (isast)
	{
		tree = ft_init_ast_tree();
		ft_init_token(&root, ROOT, ft_strdup("ROOT"));
		tree->ast_node			= ft_create_ast_node(&root);
		tree->ast_node->left	= ft_shunting_yard_build_ast(list);
		
		tree->tree_size			= ft_ast_len(tree->ast_node);
		status					= ft_validate(tree->ast_node);
		str						= ft_get_error_message(status);
		if (str)
			printf("ERROR: %s\n", str);
		free(root.token);
		// free(tree->ast_node->subshell);
		free(str);
	}						
	else
	{
		// ft_sematic_with_list();
		printf("\n/**\n * Pipe Validation\n * \n */\n// ft_sematic_with_list(t);\n");
	}
	return (tree);
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