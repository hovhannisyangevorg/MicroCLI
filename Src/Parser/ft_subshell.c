/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:25:50 by gevorg            #+#    #+#             */
/*   Updated: 2023/12/25 21:40:13 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"



void ft_handle_subshell(t_list_token* lst, t_command* cmd)
{

	t_token* token = lst->head;
	while (token && !ft_isoperator(token->type))
	{
		if (token->type == OPBREK)
		{
			t_ast_node* node = ft_get_subshell(token);
			t_ast_node* ast = ft_command_to_ast_node(cmd);
			if (node)
				ft_push_shant_stack(ast->subshell, node);
			token = ft_skip_subshell(token);
			if (!token || ft_isoperator(token->type))
				break;
		}
		token = token->next;
	}
}

t_list_token* ft_get_subshell_list(t_token* start)
{
	t_token* pos;
	t_token* end;
	
	pos = ft_find_list(OPBREK, start);
	if (!pos)
		return NULL;
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

void ft_remove_cmd_redirect(t_list_token* lst)
{
	while (lst->head && !ft_isoperator(lst->head->type))
	{
		if (ft_is_brace(lst->head->type))
			ft_remove_subshell(lst);
		else
			ft_pop_front(lst);
	}
}

t_token* ft_skip_subshell(t_token* lst)
{
	if (!lst || !ft_is_brace(lst->type))
		return lst;
	return ft_find_close_list(lst);
}

t_ast_node* ft_get_subshell(t_token* lst)
{
	t_list_token* sub;
	t_ast_node* node;
	t_token token;

	node = NULL;
	if (!lst || ft_isoperator(lst->type))
		return(NULL);
	if (lst->type == OPBREK)
	{
		sub = ft_get_subshell_list(lst);
		ft_init_token(&token, SUBSHELL, ft_strdup("SUBSHELL"));
		node = ft_create_ast_node(&token);
		if (sub->head)
			node->left = ft_shunting_yard_build_ast(sub);
	}
	return node;
}