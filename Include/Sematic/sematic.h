#ifndef 	SEMATIC_H
# define 	SEMATIC_H

# include "shell.h"


// ft_sematic.c
t_container		ft_sematic(t_list_token *list);

t_status_codes ft_validate_operator(t_ast_node* node);

t_status_codes ft_validate_command(t_ast_node* node);

t_status_codes ft_validate_redirect(t_ast_node* node);

t_status_codes ft_validate_subshell(t_ast_node* node);

t_status_codes ft_validate_argument(t_ast_node* node);

t_status_codes ft_sematic_with_tree(t_ast_node* root);

t_status_codes ft_sematic_with_list(t_command *cmd);

char*          ft_get_error_message(t_status_codes code);

#endif