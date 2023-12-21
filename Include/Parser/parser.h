# ifndef 	PARSER_H
# define 	PARSER_H


# include "shell.h"


// ft_parser.c
void		ft_parser(t_list_token *list);

// ft_helper.c
int			ft_should_ast_create(t_list_token *list);

// ft_sematic.c
void			ft_sematic(t_list_token *list, int isast);
void 			ft_build_subshell(t_ast_node *tree);

// void			ft_subtree_TST(t_ast_node *tree);

// ft_ast_functions.c
t_global_tree 	*ft_init_ast_tree();
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
int 			ft_isoperator(int type);
t_global_tree 	*ft_shunting_yard_build_ast(t_list_token *list);





void			ft_subshell(t_ast_node* node, size_t *index);


#endif