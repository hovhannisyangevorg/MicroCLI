#include "shell.h"

t_command	*ft_create_command(t_argument *argument, t_redirect *redirect, t_ast_node base)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));

	command->argument	= argument;
	command->redirect	= redirect;
	command->base 		= base;
	return (command);
}

t_argument *ft_create_argument(char **argument, t_ast_node base)
{
	t_argument	*command;

	command = malloc(sizeof(t_argument));

	command->arguments 	= argument;
	command->base 		= base;
	return (command);
}

t_redirect	*ft_create_redirect(char *arg, t_ast_node base, t_redirect_side side)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));

	if (arg)
		redirect->argument = ft_strdup(arg);
	else
		redirect->argument = NULL;
	redirect->base = base;
    redirect->side = side;
	return (redirect);
}


void ft_push_redirect(t_command *cmd, char *arg, t_token_type type, t_redirect_side side)
{
	t_token		token;
	t_ast_node	base;
	t_redirect	*new;
	t_ast_node	*tmp;

	if (!cmd)
		return ;

	ft_init_token(&token, REDIRECT, ft_get_type(type));
	ft_init_ast_node(&base, &token);
	new = ft_create_redirect(arg, base, side);

	if (!cmd->redirect)
	{
		cmd->redirect = new;
		return ;
	}
	tmp = &cmd->redirect->base;
	while (tmp && tmp->left)
		tmp = tmp->left;
	tmp->left 			= ft_redirect_to_ast_node(new);
	new->base.parent 	= tmp;
}

void ft_handle_argument(t_list_token* lst, t_command* cmd)
{
	t_ast_node		base;
	t_token			*token;
	t_token			arg;
	size_t			i;
	char			**args;

	i = 0;
	args = NULL;
	token = lst->head;
	while (token && ft_iscommand(token->type))
	{
		if (ft_is_breckets(token->type))
		{
			token = ft_skip_subshell(token);
			if (!token || !ft_iscommand(token->type))
				break;
		}
		if (token->type == TEXT && (token->prev == NULL || !ft_is_redirection(token->prev->type)))
			++i;
		token = token->next;
	}
	if (i)
	{
		args = malloc(sizeof(char*) * (i + 1));
		args[i] = NULL;
		i = 0;
		token = lst->head;
		while (token && ft_iscommand(token->type))
		{
			if (ft_is_breckets(token->type))
			{
				token = ft_skip_subshell(token);
				if (!token || !ft_iscommand(token->type))
					break ;
			}
			if (token->type == TEXT && (token->prev == NULL || !ft_is_redirection(token->prev->type)))
			{
				args[i] = ft_strdup(token->token);
				++i;
			}
			token = token->next;
		}
	}
	ft_init_token(&arg, ARGUMENT, ft_strdup("ARGUMENT"));
	ft_init_ast_node(&base, &arg);
	cmd->argument = ft_create_argument(args, base);
}

t_command	*ft_handle_command(t_list_token *list)
{
	t_ast_node 			base;
	t_token				*token;
	t_token 			temp_node;
	t_command			*comd;
	t_redirect_side 	side;

	ft_init_token(&temp_node, COMMAND, ft_strdup("COMMAND"));
	ft_init_ast_node(&base, &temp_node);
	comd 	= ft_create_command(NULL, NULL, base);

	token 	= list->head;
	side 	= PREV_BRACE;
	while (token && ft_iscommand(token->type))
	{
		if (ft_is_breckets(token->type))
		{
			token = ft_skip_subshell(token);
			if (!token || !ft_iscommand(token->type))
				break ;
            side = NEXT_BRACE;
		}
		if (ft_is_redirection(token->type))
		{
			if (token->next != NULL && token->next->type == TEXT)
				ft_push_redirect(comd, token->next->token, token->type, side);
            else
                ft_push_redirect(comd, NULL, token->type, side);
		}
		token = token->next;
	}
	ft_handle_subshell(list, comd);
	ft_handle_argument(list, comd);
	ft_remove_cmd_redirect(list);
	return (comd);
}