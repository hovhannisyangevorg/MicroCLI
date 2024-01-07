#include "shell.h"


t_argument* ft_create_argument(char** av, t_ast_node base)
{
	t_argument* arg;

	arg = malloc(sizeof(t_argument));

	arg->arguments = av;
	arg->base = base;
	return arg;
}

t_io	ft_init_io()
{
	t_io io;

	io.in = -1;
	io.out = -1;
	io.err = -1;
	return io;
}

t_io	ft_init_io_std()
{
	t_io io;

	io.in = dup(STDIN_FILENO);
	io.out = dup(STDOUT_FILENO);
	io.err = dup(STDERR_FILENO);
	return io;
}

void ft_update_command_fd(t_command* cmd, int fd, t_io_type type)
{
	if (type == STDIN)
		cmd->io.in = dup(fd);
	else if (type == STDOUT)
		cmd->io.out = dup(fd);
	else
		cmd->io.err = dup(fd);
}

t_command* ft_create_command(t_argument* arg, t_redirect* redirect, t_ast_node base)
{
	t_command* command;

	command = malloc(sizeof(t_command));

	command->argument = arg;
	command->redirect = redirect;
	command->base = base;
	command->io = ft_init_io();
	return command;
}

t_redirect* ft_create_redirect(char* arg, t_ast_node base, t_redirect_side side)
{
	t_redirect* redirect;

	redirect = malloc(sizeof(t_redirect));

	if (arg)
		redirect->argument = ft_strdup(arg);
	else
		redirect->argument = NULL;
	redirect->base = base;
    redirect->side = side;
	return redirect;
}


void ft_push_redirect(t_command* cmd, char* arg, t_token_type type, t_redirect_side side)
{
	if (!cmd)
		return ;
	t_token token;
	t_ast_node base;
	t_redirect* new;

	ft_init_token(&token, REDIRECT, ft_get_type(type));
	ft_init_ast_node(&base, &token);
	new = ft_create_redirect(arg, base, side);

	if (!cmd->redirect)
	{
		cmd->redirect = new;
		return ;
	}
	t_ast_node* tmp = &cmd->redirect->base;
	while (tmp && tmp->left)
		tmp = tmp->left;
	tmp->left = ft_redirect_to_ast_node(new);
	new->base.parent = tmp;
}

t_command* ft_handle_command(t_list_token* lst)
{
	t_command* cmd;
	t_ast_node base;
	t_token comm;
	t_token* token;
	t_redirect_side side;

	ft_init_token(&comm, COMMAND, ft_strdup("COMMAND"));
	ft_init_ast_node(&base, &comm);

	cmd = ft_create_command(NULL, NULL, base);
	token = lst->head;
    side = PREV_BRACE;
	while (token && !ft_isoperator(token->type))
	{
		if (ft_is_brace(token->type))
		{
			token = ft_skip_subshell(token);
			if (!token || ft_isoperator(token->type))
				break;
            side = NEXT_BRACE;
		}
		if (ft_is_redirection(token->type))
		{
			if (token->next != NULL && token->next->type == TEXT)
				ft_push_redirect(cmd, token->next->token, token->type, side);
            else
                ft_push_redirect(cmd, NULL, token->type, side);
		}
		token = token->next;
	}
	ft_handle_subshell(lst, cmd);
	ft_handle_argument(lst, cmd);
	ft_remove_cmd_redirect(lst);
	return cmd;
}

void ft_handle_argument(t_list_token* lst, t_command* cmd)
{
	t_token *token;
	t_token arg;
	size_t i = 0;
	char** args;
	t_ast_node base;

	args = NULL;
	token = lst->head;
	while (token && !ft_isoperator(token->type))
	{
		if (ft_is_brace(token->type))
		{
			token = ft_skip_subshell(token);
			if (!token || ft_isoperator(token->type))
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
		while (token && !ft_isoperator(token->type))
		{
			if (ft_is_brace(token->type))
			{
				token = ft_skip_subshell(token);
				if (!token || ft_isoperator(token->type))
					break;
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