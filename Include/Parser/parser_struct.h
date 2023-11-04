#ifndef 	PARSER_STRUCT_H
# define 	PARSER_STRUCT_H

// typedef union u_state t_state; 
// typedef struct s_ast_node t_ast_node;

union u_state
{
	char*	token;
};


struct s_ast_node
{
	int			type;
	t_ast_node *left;
	t_ast_node *right;
	// t_state state;

};

// struct s_ast
// {
// 	t_ast_node* root;
// }




#endif