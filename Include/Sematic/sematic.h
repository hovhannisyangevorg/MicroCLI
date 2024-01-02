#ifndef 	SEMATIC_H
# define 	SEMATIC_H

# include "shell.h"


t_status_codes ft_validate_operator(t_ast_node* node);

t_status_codes ft_validate_command(t_ast_node* node);

t_status_codes ft_validate_redirect(t_ast_node* node);

t_status_codes ft_validate_subshell(t_ast_node* node);

t_status_codes ft_validate_argument(t_ast_node* node);

t_status_codes ft_validate(t_ast_node* root);

char*          ft_get_error_message(t_status_codes code);

#endif