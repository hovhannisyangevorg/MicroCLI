#ifndef EXECUTOR_H
# define EXECUTOR_H

# include 	"shell.h"

size_t ft_count_pipes(t_ast_node* tree);

void ft_executor(t_container* cont);

/*
 * function that automatically called when stored as list 
*/
void ft_execute_list(t_list_token* list);

/*
 * function that automatically called when stored as syntax tree 
*/
void ft_execute_syntax_tree(t_global_tree* tree);

t_io    ft_init_io();

t_io	ft_init_io_std();

int ft_update_command_io(t_command* cmd, int fd, t_io_type type);

#endif