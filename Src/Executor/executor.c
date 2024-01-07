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

/*
 * function that automatically called when stored as list
*/
void ft_execute_list(t_list_token* list)
{
    (void)list;
    printf("%s\n", "list");
}

int ft_update_command_io(t_command* cmd, int fd, t_io_type type)
{
    if (type == STDIN)
        return dup2(cmd->io.in, fd);
    if (type == STDOUT)
        return dup2(cmd->io.out, fd);
    return dup2(cmd->io.err, fd);
}

/*
 * function that automatically called when stored as syntax tree 
*/
void ft_execute_syntax_tree(t_global_tree* tree)
{

    size_t pipeCount = ft_count_pipes(tree->ast_node);

    int fd2 = open("hello.txt", O_CREAT | O_RDWR, 0777);
    int fd = dup(STDOUT_FILENO);
    // dup2(fd2, STDOUT_FILENO);
    // dup2(fd2, STDIN_FILENO);
    dup2(fd2, STDERR_FILENO);
    // close(STDOUT_FILENO);
    (void)fd;
    fprintf(stderr, "pc: %lu\n", pipeCount);
}

void ft_executor(t_container* cont)
{
    cont->handler(cont);
}