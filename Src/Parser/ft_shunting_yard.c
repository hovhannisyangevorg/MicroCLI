/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shunting_yard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:00:12 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/24 20:51:39 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_isoper(int type)
{
	return (type != TEXT);
}

t_global_tree *ft_shunting_yard_build_ast(t_list_token *list)
{
	t_ast_node			*ast_node;
	t_ast_node 			*ast_left;
	t_ast_node 			*ast_right;

	t_token 			token;
	t_token				tmp_token;
	
	t_global_tree 		*tree;
	t_global_stack 		*stack_opre;
	t_global_stack 		*stack_oute;
	
	tree 				= ft_init_ast_tree();
	stack_opre			= ft_init_shant_stack();
	stack_oute			= ft_init_shant_stack();
	
	ast_node 			= NULL;

	while (list->head && list->head->type != 0)
	{
		ft_init_token(&token, list->head->type, ft_strdup(list->head->token));
		ft_pop_front(list);

		if (ft_isoper(token.type))
		{
			while (stack_opre->size && ft_isoper(stack_opre->top->ast_node->token_type))
			{
				if (stack_oute->size)
					ast_right = stack_oute->top->ast_node;
				else
					ast_right = NULL;

				ft_pop_shant_stack(stack_oute);

				if (stack_oute->size)
					ast_left = stack_oute->top->ast_node;
				else
					ast_left = NULL;

				ft_pop_shant_stack(stack_oute);
				
				ft_init_token(&tmp_token, stack_opre->top->ast_node->token_type, ft_strdup(stack_opre->top->ast_node->token));
				ast_node 		= ft_create_ast_node(&tmp_token);
				ast_left->parent = ast_node;
				ast_right->parent = ast_node;
				ast_node->left 	= ast_left;
				ast_node->right = ast_right;
			
				ft_push_shant_stack(stack_oute, ast_node);
				ft_pop_shant_stack(stack_opre);
				free(tmp_token.token);	
			}
			ft_push_shant_stack(stack_opre, ft_create_ast_node(&token));
		}
		else
		{
			ft_push_shant_stack(stack_oute, ft_create_ast_node(&token));
		}
		
		free(token.token);
	}

	while (stack_opre->size)
	{
		if (stack_oute->size)
			ast_right = stack_oute->top->ast_node;
		else
			ast_right = NULL;
		
		ft_pop_shant_stack(stack_oute);
		
		if (stack_oute->size)
			ast_left = stack_oute->top->ast_node;
		else
			ast_left = NULL;	
			
		ft_pop_shant_stack(stack_oute);
		ft_init_token(&token, stack_opre->top->ast_node->token_type, ft_strdup(stack_opre->top->ast_node->token));
		ast_node = ft_create_ast_node(&token);
		ast_left->parent = ast_node;
		ast_right->parent = ast_node;
		ast_node->left = ast_left;
		ast_node->right = ast_right;
		ft_push_shant_stack(stack_oute, ast_node);
		ft_pop_shant_stack(stack_opre);
		free(token.token);
	}
	if (list->size)
		ft_pop_front(list);
	tree->ast_node = stack_oute->top->ast_node;
	tree->tree_size = ft_ast_len(tree->ast_node);

	ft_print_list(*list);

	return (tree);
}
