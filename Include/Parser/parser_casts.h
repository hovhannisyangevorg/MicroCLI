#ifndef PARSER_CASTS_H
#define PARSER_CASTS_H

#include "parser.h"

// ft_casts.c
t_ast_node* ft_command_to_ast_node(t_command* cmd);

t_ast_node* ft_redirect_to_ast_node(t_redirect* rd);

t_ast_node* ft_argument_to_ast_node(t_argument* arg);

t_command* ft_ast_to_command(t_ast_node* ast);

t_argument* ft_ast_to_argument(t_ast_node* ast);

t_redirect* ft_ast_to_redirect(t_ast_node* ast);

t_list_token* ft_container_to_list(t_container* cont);

t_global_tree* ft_container_to_tree(t_container* cont);

t_container* ft_tree_to_container(t_global_tree* tree);

t_container* ft_list_to_container(t_list_token* list);

#endif