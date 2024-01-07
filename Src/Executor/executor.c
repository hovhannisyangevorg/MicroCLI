#include "shell.h"

size_t ft_count_pipes(t_ast_node* root)
{
    size_t left = 0;
    size_t right = 0;
    if (!root)
        return 0;
    if (root->token_type == PIPE)
    {
        left = ft_count_pipes(root->left);
        right = ft_count_pipes(root->right);
        return left + right + 1;
    }
    left = ft_count_pipes(root->left);
    right = ft_count_pipes(root->right);
    return left + right;
}


void ft_execute_list(t_list_token* list)
{
    (void)list;
    printf("%s\n", "list");
}

void ft_execute_syntax_tree(t_global_tree* tree)
{
    // t_global_tree* tree;

    // tree = ft_container_to_tree(cont);
    size_t pipeCount = ft_count_pipes(tree->ast_node);
    // (void)tree;
    printf("pc: %lu\n", pipeCount);
}

void ft_executor(t_container* cont)
{
    cont->handler(cont);
}