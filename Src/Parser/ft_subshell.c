/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:25:50 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/29 13:49:51 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_handle_subshell(t_list_token *list, t_command *command)
{
	t_ast_node	*ast_node;
	t_ast_node	*node;
	t_token		*token;

	token = list->head;
	while (token && ft_iscommand(token->type))
	{
		if (token->type == OPBREK)
		{
			node			= ft_get_subshell(token);
			ast_node		= ft_command_to_ast_node(command);
			if (node)
				ft_push_shant_stack(ast_node->subshell, node);
			token = ft_skip_subshell(token);
			if (!token || !ft_iscommand(token->type))
				break ;
		}
		token = token->next;
	}
}

t_list_token *ft_get_subshell_list(t_token *open_brek)
{
	t_token *pos;
	t_token *end;
	
	pos = ft_find_list(OPBREK, open_brek);
	if (!pos)
		return (NULL);
	end = ft_find_close_list(pos);
	if (!end)
		return (NULL);
	return (ft_sublist(pos->next, end));
}


void ft_remove_subshell(t_list_token* lst)
{
	t_token* end;


	end = ft_find_close_list(lst->head);
	if (!end || !lst->head)
		return ;
	while (lst->head != end->next)
		ft_pop_front(lst);
}

void ft_remove_command_redirect(t_list_token* lst)
{
	while (lst->head && ft_iscommand(lst->head->type))
	{
		if (ft_is_breckets(lst->head->type))
			ft_remove_subshell(lst);
		else
			ft_pop_front(lst);
	}
}

t_token *ft_skip_subshell(t_token *list)
{
	if (!list || !ft_is_breckets(list->type))
		return (list);
	return (ft_find_close_list(list));
}

t_ast_node *ft_get_subshell(t_token *open_brek)
{
	t_list_token	*sub_list;
	t_ast_node		*node;
	t_token			token;

	node = NULL;
	if (!open_brek || !ft_iscommand(open_brek->type))
		return (NULL);
	if (open_brek->type == OPBREK)
	{
		sub_list = ft_get_subshell_list(open_brek);
		ft_init_token(&token, SUBSHELL, ft_strdup("SUBSHELL"));
		node = ft_create_ast_node(&token);
		if (sub_list->head)
			node->left = ft_shunting_yard_build_ast(sub_list);
		free(token.token);
	}
	return (node);
}