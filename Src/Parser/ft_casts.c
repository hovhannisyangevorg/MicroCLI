#include "shell.h"


t_ast_node* ft_command_to_ast_node(t_command* cmd)
{
	return (t_ast_node* )cmd;
}

t_ast_node* ft_redirect_to_ast_node(t_redirect* rd)
{
	return (t_ast_node* )rd;
}

t_ast_node* ft_argument_to_ast_node(t_argument* arg)
{
	return (t_ast_node* )arg;
}

t_command* ft_ast_to_command(t_ast_node* ast)
{
	return (t_command* )ast;
}

t_argument* ft_ast_to_argument(t_ast_node* ast)
{
	return (t_argument* )ast;
}

t_redirect* ft_ast_to_redirect(t_ast_node* ast)
{
	return (t_redirect* )ast;
}

t_function_entity* ft_entity_to_function(t_hash_entity* hash)
{
	return (t_function_entity* )hash;
}

t_env_entity* ft_entity_to_env(t_hash_entity* hash)
{
	return (t_env_entity* )hash;
}


t_hash_entity* ft_function_to_entity(t_function_entity* func)
{
	return (t_hash_entity* )func;
}

t_hash_entity* ft_env_to_entity(t_env_entity* env)
{
	return (t_hash_entity* )env;
}

t_list_token* ft_container_to_list(t_container* cont)
{
	return (t_list_token* )cont;
}

t_global_tree* ft_container_to_tree(t_container* cont)
{
	return (t_global_tree* )cont;
}

t_container* ft_tree_to_container(t_global_tree* tree)
{
	return (t_container* )tree;
}

t_container* ft_list_to_container(t_list_token* list)
{
	return (t_container* )list;
}