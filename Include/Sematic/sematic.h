#ifndef 	SEMATIC_H
# define 	SEMATIC_H

# include "shell.h"

// void		ft_parser(t_list_token *list);
// int			ft_should_ast_create(t_list_token *list);
// void		ft_sematic(t_list_token *list, int is_create);
t_ast_node* ft_ast_left(t_ast_node* root);
t_ast_node* ft_ast_right(t_ast_node* root);
#endif