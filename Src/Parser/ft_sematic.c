/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sematic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:08:20 by gevorg            #+#    #+#             */
/*   Updated: 2023/11/27 17:49:26 by gevorg           ###   ########.fr       */
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
// 			t_global_tree* sub_tree = ft_sematic_with_tree(sub_list);
// 			tree->token_type = SUBSHELL;
// 			tree->left = sub_tree->ast_node;	
// 		}

// 	}
// 	correct_tree(tree->left);
// 	correct_tree(tree->right);
// }





































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
// 			t_global_tree* sub_tree = ft_sematic_with_tree(sub_list);
// 			tree->token_type = SUBSHELL;
// 			tree->left = sub_tree->ast_node;	
// 		}

// 	}
// 	correct_tree(tree->left);
// 	correct_tree(tree->right);
// }































































void ft_subshell_convert_type(t_ast_node *tree)
{
	if (!tree)
		return ;

	if (tree->token_type == TEXT)
	{
		if (ft_strchr(tree->token, OPBREK) || ft_strchr(tree->token, CLBREK))
				tree->token_type = SUBSHELL;
	}
	ft_subshell_convert_type(tree->left);
	ft_subshell_convert_type(tree->right);
}



// void	ft_subtree_TST(t_ast_node *tree)
// {
// 	t_list_token *sub_list;
// 	t_ast_node 	*sub_tree;

// 	sub_list = ft_multi_split(tree->token, SEPARARTORS, 1);
// 	ft_ordering(sub_list);
// 	printf("\nIs a sublist\n");
// 	ft_print_list(*sub_list);
// 	sub_tree = ft_create_ast_node(sub_list->head);
// 	ft_subshell_convert_type(sub_tree);
// 	ft_subtree_TST(tree->left);
// 	ft_subtree_TST(tree->midle);
// 	ft_subtree_TST(tree->right);
// }


void ft_create_subtree(t_ast_node *tree)
{
	if (!tree)
		return ;

	if (tree->token_type == SUBSHELL)
	{
		ft_subtree_TST(tree);
	}
	
	ft_create_subtree(tree->left);
	ft_create_subtree(tree->right);
}





t_global_tree	*ft_sematic_with_tree(t_list_token *list)
{
	t_global_tree *tree;

	tree = ft_shunting_yard_build_ast(list);
	
	return (tree);	
}


void	ft_sematic(t_list_token *list, int isast)
{
	t_global_tree *tree;
	
	if(isast)
	{
		tree = ft_sematic_with_tree(list);
		ft_subshell_convert_type(tree->ast_node);
		ft_create_subtree(tree->ast_node);

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