/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:41:20 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/08 21:37:36 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_status_codes ft_callback(t_status_codes code, t_callback callback, t_ast_node* node)
{
	if (!code)
		return callback(node);
	return code;
}

t_status_codes ft_validate_operator(t_ast_node* node)
{
	if (!node)
		return SUCCESS_CODE;
	if (!node->left || !node->right)
		return MISSING_TOKEN;
	return SUCCESS_CODE;
}

t_status_codes ft_validate_command(t_ast_node* node)
{
	t_command* cmd;
	t_redirect* redirect;
	t_argument* argument;
	t_ast_node*	reds;
	t_status_codes status;

	if (!node)
		return SUCCESS_CODE;

	status = SUCCESS_CODE;
	cmd = ft_ast_to_command(node);
	redirect = cmd->redirect;
	argument = cmd->argument;
	if (argument && argument->arguments && cmd->base.subshell->size)
		return MISSING_OPERATOR;
	if (redirect && redirect->side == PREV_BRACE && cmd->base.subshell->size)
		return MISSING_OPERATOR;
	reds = &redirect->base;
	while (reds)
	{
		status = ft_callback(status, ft_validate_redirect, reds);
		reds = reds->left;
	}
	return status;
}
t_status_codes ft_validate_redirect(t_ast_node* node)
{
	t_redirect* redirect;

	if (!node)
		return SUCCESS_CODE;
	redirect = ft_ast_to_redirect(node);
	if (!redirect->argument)
		return UNEXPECTED_REDIRECT;
	return SUCCESS_CODE;
}
t_status_codes ft_validate_subshell(t_ast_node* node)
{
	if (!node)
		return SUCCESS_CODE;
	if (node->subshell->size > 1)
		return MISSING_OPERATOR;
	return SUCCESS_CODE;
}

t_status_codes ft_validate_empty(t_ast_node* node)
{
	if (!node)
		return SUCCESS_CODE;
	if (!node->left && !node->right)
		return EMPTY_SUBSHELL;
	return SUCCESS_CODE;
}


t_status_codes ft_validate(t_ast_node* root)
{
	t_shant_stack* node;
	t_status_codes status = SUCCESS_CODE;

	if (!root)
		return SUCCESS_CODE;
	if (root->token_type == ROOT)
		return ft_validate(root->left);
	if (root->token_type == COMMAND)
		status = ft_callback(status, ft_validate_command, root);
	else if (root->token_type == REDIRECT)
		status = ft_callback(status, ft_validate_redirect, root);
	else if (ft_isoperator(root->token_type))
		status = ft_callback(status, ft_validate_operator, root);
	status = ft_callback(status, ft_validate_subshell, root);
	node = root->subshell->top;
	while (node)
	{
		status = ft_callback(status, ft_validate_empty, node->ast_node);
		status = ft_callback(status, ft_validate, node->ast_node);
		node = node->next;
	}
	status = ft_callback(status, ft_validate, root->left);
	status = ft_callback(status, ft_validate, root->right);
	return status;
}