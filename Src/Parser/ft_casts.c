#include "shell.h"


t_ast_node* ft_command_to_ast_node(t_command* cmd)
{
	return ((t_ast_node* )((char*)cmd - offsetof(t_command, base)));
}

t_ast_node* ft_redirect_to_ast_node(t_redirect* rd)
{
	return ((t_ast_node* )((char*)rd - offsetof(t_redirect, base)));
}

t_ast_node* ft_argument_to_ast_node(t_argument* arg)
{
	return ((t_ast_node* )((char*)arg - offsetof(t_argument, base)));
}

t_command* ft_ast_to_command(t_ast_node* ast)
{
	return ((t_command* )((char*)ast + offsetof(t_command, base)));
}

t_argument* ft_ast_to_argument(t_ast_node* ast)
{
	return ((t_argument* )((char*)ast + offsetof(t_argument, base)));
}

t_redirect* ft_ast_to_redirect(t_ast_node* ast)
{
	return ((t_redirect* )((char*)ast + offsetof(t_redirect, base)));
}