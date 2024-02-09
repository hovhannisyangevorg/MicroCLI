/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sematic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:08:20 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/08 22:13:35 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_container ft_sematic(t_list_token *list)
{
	t_container		container;
	t_global_tree 	*tree;
	t_token 		root;
	t_status_codes	status;
	char			*str;

	tree = NULL;
	// container.fd = ft_init_io_std();
	if (ft_should_ast_created(list))
	{
		tree = ft_init_ast_tree();
		ft_init_token(&root, ROOT, ft_strdup("ROOT"));
		tree->ast_node			= ft_create_ast_node(&root);
		tree->ast_node->left	= ft_shunting_yard_build_ast(list);
		tree->tree_size			= ft_ast_len(tree->ast_node);
		container.tree 			= tree;
		container.exec_type 	= TREE;
		status					= ft_sematic_with_tree(tree->ast_node);
		container.exit_status 	= status;
		str						= ft_get_error_message(status);
		if (str)
		{
			ft_panic_shell("ERROR: ", str);
		}
		free(root.token);
		free(str);
	}						
	else
	{
		container.exec_type		= LIST;
		container.command		= ft_handle_command(list);
		container.exit_status 	= ft_sematic_with_list(container.command);
		str						= ft_get_error_message(container.exit_status);
		if (str)
			ft_panic_shell("ERROR: ", str);
		free(str);
	}
	return (container);
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