/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:58:30 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/27 17:23:22 by gevorg           ###   ########.fr       */
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
	ft_init_arrey(&pipe_fd, ((pipe_count + 1) * 2));

	while (++i < pipe_count + 1)
	{
		pipe(pipe_fd.arr + j);
		j += 2;
	}
	
	return (pipe_fd);
}

// DFS Inorder Traversal

void	ft_assign_pipe_fd(t_ast_node *tree, t_vector *pipe_fd, size_t* pipe_iter)
{
	if (!tree)
	{
		// printf("\n1---------1---------1\n");
		return ;
	}

	ft_assign_pipe_fd(tree->left, pipe_fd, pipe_iter);
	
	if (tree->token_type == COMMAND)
	{	
		t_command *command = ft_ast_to_command(tree);
		printf("size: %lu %lu\n", pipe_fd->capacity, *pipe_iter);
		command->io.input	= pipe_fd->arr[(*pipe_iter)++];
		command->io.output	= pipe_fd->arr[(*pipe_iter)++];
	}
	ft_assign_pipe_fd(tree->right, pipe_fd, pipe_iter);

}




// void	ft_open_proces(size_t pipe_count)
// {
	
// }

// void	ft_open_wait(size_t pipe_count)
// {
	
// }