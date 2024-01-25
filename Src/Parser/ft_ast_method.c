/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_method.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:52:35 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/25 23:22:22 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_global_tree 	*ft_init_ast_tree()
{
	t_global_tree *tree = (t_global_tree *)malloc(sizeof(t_global_tree));
	if (!tree)
		return (NULL);
	tree->ast_node = NULL;
	tree->tree_size = 0;
	return (tree);
}

t_ast_node 	*ft_create_ast_node(t_token *token)
{
    t_ast_node *new_node;
	
	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
    if (!new_node)
		return (NULL);
	
    new_node->token_type 	= token->type;
	new_node->parent		= NULL;
    new_node->token 		= ft_strdup(token->token);
    new_node->quate_type 	= 0;
    new_node->left 			= NULL;
	new_node->subshell		= ft_init_shant_stack();
    new_node->right 		= NULL;
    return (new_node);
}

size_t ft_ast_len(t_ast_node* root)
{
	if (!root)
		return (0);
	size_t left = 0;
	size_t right = 0;
	
	left = ft_ast_len(root->left);
	right = ft_ast_len(root->right);
	return (left + right + 1);
}

void ft_init_ast_node(t_ast_node* node, t_token* token)
{
	if (!node)
		return;	
    node->token_type 	= token->type;
	node->parent		= NULL;
    node->token 		= ft_strdup(token->token);
    node->quate_type 	= 0;
    node->left 			= NULL;
	node->subshell		= ft_init_shant_stack();
    node->right 		= NULL;
}

static char	*ft_ast_strjoin(char *s1, char *s2)
{
	char		*new_str;
	size_t		f_index;
	size_t		s_index;

	if (!(new_str = malloc(sizeof(char) *
					(ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1))))
		return (NULL);
	f_index = 0; 
	s_index = 0;
	if (s1)
		while (s1[f_index])
			new_str[s_index++] = s1[f_index++];
	f_index = 0;
	if (s2)
		while (s2[f_index])
			new_str[s_index++] = s2[f_index++];
	new_str[s_index] = '\0';
	return (new_str);
}

void print_redirect(t_ast_node* redirect)
{
	t_redirect* red = ft_ast_to_redirect(redirect);
	printf("REDIRECT { type: %d, token: %s, arg: %s", redirect->token_type, redirect->token, red->argument);
}

void print_argument(t_ast_node* arg)
{
	t_argument* argument = ft_ast_to_argument(arg);
	printf("ARGUMENT { type: %d, token: %s", arg->token_type, arg->token);
	printf(", args = [ ");
	if (!argument->arguments || !argument->arguments[0])
		printf("null");
	else
	{
		size_t i = 0;
		while (argument->arguments && argument->arguments[i])
		{
			printf("%s", argument->arguments[i]);
			++i;
			if (argument->arguments[i])
				printf(", ");
		}
	}
	printf(" ]");
}

void print_command(t_ast_node* command, char *prefix, int is_root, int is_left)
{
	t_command* cmd = ft_ast_to_command(command);
	printf("COMMAND { type: %d, token: %s, fds: [in: %d, out: %d, err: %d]", command->token_type, command->token, cmd->io.input, cmd->io.output, cmd->io.error);
	t_ast_node* args = ft_argument_to_ast_node(cmd->argument);
	t_ast_node* red = ft_redirect_to_ast_node(cmd->redirect);
	if ( is_root == 0 )
		{
			if (is_left)
				printf(", L");
			else
				printf(", R");
		}
		printf(" } \n");
		char *str;
		if (is_left)
			str = ft_ast_strjoin(prefix, "│      ");
		else
			str = ft_ast_strjoin(prefix, "       ");
	t_shant_stack* node = cmd->base.subshell->top;
	while (node)
	{
		ft_ast_print(node->ast_node, str, 1, 0);
		node = node->next;
	}
	ft_ast_print(args, str, 1, 0);
	ft_ast_print(red, str, 0, 0);
	free(str);
}

void print_node_type(t_ast_node* node, char *prefix, int is_root, int is_left)
{
	switch (node->token_type)
	{
	case COMMAND:
		print_command(node, prefix, is_root, is_left);
		break;
	case ARGUMENT:
		print_argument(node);
		break;
	case REDIRECT:
		print_redirect(node);
		break;
	default:
		printf("AST_NODE { type: %d, token: %s", node->token_type, node->token);
		break;
	}
}

void ft_ast_print(t_ast_node *head, char *prefix, int is_left, int is_root)
{
	if (head != NULL)
	{
		printf("%s│\n%s", prefix, prefix);
		if (is_left || is_root)
		{
			printf("├───");
		}
		else
			printf("└───");
		print_node_type(head, prefix, is_root, is_left);
		if (head->token_type == COMMAND)
		{
			return;
		}
		if ( is_root == 0 )
		{
			if (is_left)
				printf(", L");
			else
				printf(", R");
		}
		printf(" } \n");
		char *str;
		if (is_left)
			str = ft_ast_strjoin(prefix, "│      ");
		else
			str = ft_ast_strjoin(prefix, "       ");
		
		t_shant_stack* node = head->subshell->top;
		while (node)
		{
			ft_ast_print(node->ast_node, str, 1, 0);
			node = node->next;
		}
		ft_ast_print(head->left, str, 1, 0);
		ft_ast_print(head->right, str, 0, 0);
		free(str);
	}
	else
	{
		printf("%s", prefix);
		if (is_left || is_root)
			printf("├───");
		else
			printf("└───");
		printf("AST_NODE { NULL");
		if ( is_root == 0 )
		{
			if (is_left)
				printf(", L");
			else
				printf(", R");
		}
		printf(" } \n");
	}
}