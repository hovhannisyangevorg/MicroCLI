# ifndef 	PARSER_H
# define 	PARSER_H


# include "parser_struct.h"
# include "shell.h"

void		ft_parser(t_list_token *list);
int			ft_should_ast_create(t_list_token *list);

#endif