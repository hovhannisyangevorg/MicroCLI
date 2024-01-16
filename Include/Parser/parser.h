# ifndef 	PARSER_H
# define 	PARSER_H


# include "shell.h"
# include "parser_casts.h"


// ft_parser.c
t_container *ft_parser(t_list_token *list);

// ft_helper.c
int			ft_should_ast_create(t_list_token *list);

// ft_sematic.c
t_container *ft_sematic(t_list_token *list, int isast);

// ft_ast_functions.c
t_global_tree 	*ft_init_ast_tree();
void            ft_init_ast_node(t_ast_node* node, t_token* token);
t_ast_node 		*ft_create_ast_node(t_token *token);
size_t 			ft_ast_len(t_ast_node* root);
void 			ft_ast_print(t_ast_node *head, char *prefix, int is_left, int is_root);

// ft_shant_stack.c
t_global_stack 	*ft_init_shant_stack();
t_shant_stack	*ft_push_shant_stack(t_global_stack *stack, t_ast_node *ast_node);
// void			ft_free_shant_stack(t_global_stack *stack);
int				ft_is_shant_stack_empty(t_global_stack *stack);
void			ft_pop_shant_stack(t_global_stack *stack);
void			ft_free_shant_stack(t_global_stack *stack);

// ft_shanting_yard.c
t_ast_node 	    *ft_shunting_yard_build_ast(t_list_token *list);


// ft_subshell.c
void            ft_handle_subshell(t_list_token* lst, t_command* cmd);

t_list_token*   ft_get_subshell_list(t_token* start);

void            ft_remove_subshell(t_list_token* lst);

void            ft_remove_cmd_redirect(t_list_token* lst);

t_token*        ft_skip_subshell(t_token* lst);

t_ast_node*     ft_get_subshell(t_token* lst);


// ft_build_command.c
t_argument*     ft_create_argument(char** args, t_ast_node base);

t_command*      ft_create_command(t_argument* arg, t_redirect* redirect, t_ast_node base);

t_redirect*     ft_create_redirect(char* arg, t_ast_node base, t_redirect_side side);

void            ft_push_redirect(t_command* cmd, char* arg, t_token_type type, t_redirect_side side);

t_command*      ft_handle_command(t_list_token* lst);

void            ft_handle_argument(t_list_token* lst, t_command* cmd);



#endif