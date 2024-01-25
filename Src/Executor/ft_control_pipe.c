/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:58:30 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/25 23:27:04 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_vector	ft_open_pipe_fd(size_t pipe_count)
{
	size_t		i;
	size_t		j;
	t_vector	pipe_fd;

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
void	ft_assign_pipe_fd(t_ast_node *tree, t_vector *pipe_fd)
{
	if (!tree)
		return ;
	static size_t i;
		
	ft_assign_pipe_fd(tree->left, pipe_fd);
	
	if (tree->token_type == COMMAND)
	{
		t_command *command = ft_ast_to_command(tree);
		
		command->io.input	= pipe_fd->arr[i++];
		command->io.output	= pipe_fd->arr[i++];
	}
	ft_assign_pipe_fd(tree->right, pipe_fd);

}




// void	ft_open_proces(size_t pipe_count)
// {
	
// }

// void	ft_open_wait(size_t pipe_count)
// {
	
// }