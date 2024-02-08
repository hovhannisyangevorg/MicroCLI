/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:58:30 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/08 17:18:51 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_vector	ft_open_pipe_fd(size_t pipe_count)
{
	size_t		i;
	size_t		j;
	t_vector	pipe_fd;

	// printf("pipe_counttttttt = %lu\n", pipe_count);
	i = -1;
	j = 0;
	ft_init_arrey(&pipe_fd, ((pipe_count) * 2));

	while (++i < pipe_count)
	{
		pipe(pipe_fd.arr + j);
		j += 2;
	}
	
	return (pipe_fd);
}

// DFS Inorder Traversal

// void	ft_assign_pipe_fd(t_ast_node *tree, t_vector *pipe_fd, size_t* pipe_iter)
// {
// 	if (!tree)
// 		return ;

// 	ft_assign_pipe_fd(tree->left, pipe_fd, pipe_iter);
	
// 	if (tree->token_type == PIPE)
// 	{	
// 		t_command *command = ft_ast_to_command(tree);
// 		printf("size: %lu %lu\n", pipe_fd->capacity, *pipe_iter);
// 		// dup2();
// 		command->io.input	= pipe_fd->arr[(*pipe_iter)++];
// 		command->io.output	= pipe_fd->arr[(*pipe_iter)++];
// 	}
// 	ft_assign_pipe_fd(tree->right, pipe_fd, pipe_iter);

// }









t_ast_node *ft_ast_left_most(t_ast_node *ast_node)
{
	if (ast_node->token_type == PIPE)
		return (NULL);
	if (ast_node->right)
		return (ast_node->right);
	return (ast_node);
}

// lsof -p
// TODO: write logic for rigt
int		ft_execut_command(t_command *command, t_hash_table *env, t_vector *pipe_fd, size_t pipe_iter)
{
	(void)env;
	int pid = fork();
	if (pid == -1)
	{
		return (-1);
	} else if (pid == 0) 
	{
		if (pipe_iter != 0)
			dup2(pipe_fd->arr[(pipe_iter - 1) * 2], STDIN_FILENO);
		if (pipe_iter != pipe_fd->size / 2)
			dup2(pipe_fd->arr[(pipe_iter * 2) + 1], STDOUT_FILENO);
		for (size_t i = 0; i < pipe_fd->size; ++i)
			close(pipe_fd->arr[i]);
		execve(command->argument->arguments[0], command->argument->arguments, NULL);

		perror("execve: ");
		exit(EXIT_FAILURE);
	}
	return(0);
}


int		ft_open_process_for_pipe(t_ast_node *tree, t_hash_table *env, t_vector *pipe_fd, size_t* pipe_iter)
{
	t_ast_node *ast_node;


	if (*pipe_iter <= pipe_fd->size / 2)
	{
		ast_node = ft_ast_left_most(tree->left);
		if (ast_node)
		{
			ft_execut_command(ft_ast_to_command(ast_node), env, pipe_fd, *pipe_iter);
			(*pipe_iter)++;
		}

		ft_execut_command(ft_ast_to_command(tree->right), env, pipe_fd, *pipe_iter);
		(*pipe_iter)++;
	}
	
	return(0);
}	

// TODO: open wait for process and close unclosd fd
void	ft_execute_part(t_ast_node *tree, t_hash_table *env, t_vector *pipe_fd, size_t* pipe_iter)
{
	if (!tree)
		return ;

	ft_execute_part(tree->left, env, pipe_fd, pipe_iter);
	
	if (tree->token_type == PIPE)
	{
		ft_open_process_for_pipe(tree, env, pipe_fd, pipe_iter);
		return;
	}
	ft_execute_part(tree->right, env, pipe_fd, pipe_iter);
}







// void	ft_open_proces(size_t pipe_count)
// {
	
// }

// void	ft_open_wait(size_t pipe_count)
// {
	
// }