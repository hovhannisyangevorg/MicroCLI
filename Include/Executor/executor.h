#ifndef EXECUTOR_H
# define EXECUTOR_H

# include 	"shell.h"

size_t ft_count_pipes(t_ast_node* tree);

void ft_executor(t_container* cont);

void ft_execute_list(t_list_token* list);

void ft_execute_syntax_tree(t_global_tree* tree);

#endif