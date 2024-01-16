/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shunting_yard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:00:12 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/16 15:43:00 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast_node	*ft_shunting_yard_build_ast(t_list_token *list)
{
	t_ast_node			*node;
	t_ast_node			*ast_node;
	t_ast_node 			*ast_left;
	t_ast_node 			*ast_right;

	t_token 			token;
	t_token				tmp_token;

	t_command			*command;	
	t_global_stack 		*stack_opre;
	t_global_stack 		*stack_oute;
	
	stack_opre			= ft_init_shant_stack();
	stack_oute			= ft_init_shant_stack();
	
	ast_node 			= NULL;

	while (list->head)
	{
		ft_init_token(&token, list->head->type, ft_strdup(list->head->token));
		ft_pop_front(list);
		if (!ft_iscommand(token.type))
		{
			while (stack_opre->size && !ft_iscommand(stack_opre->top->ast_node->token_type))
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
				if (ast_left)
					ast_left->parent = ast_node;
				if (ast_right)
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
			ft_push_front(list, token.type, ft_strdup(token.token));
			command		= ft_handle_command(list);
			node		= ft_command_to_ast_node(command);
			ft_push_shant_stack(stack_oute, node);
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
		if (ast_left)
			ast_left->parent = ast_node;
		if (ast_right)
			ast_right->parent = ast_node;
		ast_node->left = ast_left;
		ast_node->right = ast_right;
		ft_push_shant_stack(stack_oute, ast_node);
		ft_pop_shant_stack(stack_opre);
		free(token.token);
	}
	if (list->size)
		ft_pop_front(list);
	return (stack_oute->top->ast_node);
}
