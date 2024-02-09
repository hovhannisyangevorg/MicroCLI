/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:58:30 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/08 22:47:36 by gevorg           ###   ########.fr       */
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
	if (!ast_node || ast_node->token_type == PIPE)
		return (NULL);
	if (ast_node->right)
		return (ast_node->right);
	return (ast_node);
}



void ft_hendle_pipe(t_vector * pipe_fd, size_t pipe_iter)
{
	size_t i;

	i = 0;
	if (pipe_iter != 0)
		dup2(pipe_fd->arr[(pipe_iter - 1) * 2], STDIN_FILENO);
	if (pipe_iter != pipe_fd->size / 2)
		dup2(pipe_fd->arr[(pipe_iter * 2) + 1], STDOUT_FILENO);
	while (i < pipe_fd->size)
		close(pipe_fd->arr[i++]);
}



int ft_command_fron_PATH(t_command *command, t_hash_table *env)
{
	size_t i;
	char **paths;
	char *path_exec;
	char *prefix;
	int	 status;
	
	i 		= 0;
	status	= EXIT_SUCCESS;
	prefix	= NULL;
	path_exec = ft_strdup(command->argument->arguments[0]);
	
	if (path_exec[0] == '/' || !ft_strncmp(path_exec, "./", 2) || !ft_strncmp(path_exec, "../", 3))
	{
		status = access (path_exec, F_OK | X_OK);
		free(path_exec);
		return (errno);	
	}
	else
	{
		
		paths = ft_split(ft_get_env(env, "PATH"), ':');
		while (paths[i])
		{
			prefix = ft_strdup(paths[i]);
			prefix = ft_gnl_strjoin(prefix, "/");
			prefix = ft_strjoin(prefix, path_exec);
			status = access(prefix, F_OK | X_OK);
			if (!status)
			{
				free(command->argument->arguments[0]);
				command->argument->arguments[0] = prefix;
				return (status);
			}
			i++;
		}
		ft_vecstrdel(&paths);
		
	}

	free(path_exec);
	return (status);
}

// lsof -p
// TODO: write logic for rigt
// TODO: check file permissions in redirection part
int		ft_execut_command(t_command *command, t_hash_table *env_table, t_hash_table *function_table, t_vector *pipe_fd, size_t pipe_iter)
{
	(void)function_table;
	char **env = ft_convert_env_to_args(env_table);
	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) 
	{
		ft_hendle_pipe(pipe_fd, pipe_iter);
		// t_function_callback biltin_func =  ft_get_function(function_table, command->argument->arguments[0]);
		// if (biltin_func)
		// {
		// 	int status = biltin_func(command, env_table);
		// 	char* st = ft_itoa(status);
		// 	// ft_set_env(env_table, "?", st, 1);
		// 	exit(status);
		// }
		printf("pid: %s\n", ft_get_env(env_table, "$"));
		ft_command_fron_PATH(command, env_table);
		printf("exec: %s\n", command->argument->arguments[0]);
		execve(command->argument->arguments[0], command->argument->arguments, env);
			
			
		perror("execve: ");
		exit(EXIT_FAILURE);
	}
	return(0);
}


int		ft_open_process_for_pipe(t_ast_node *tree, t_hash_table *env, t_hash_table *function_table, t_vector *pipe_fd, size_t* pipe_iter)
{
	t_ast_node *ast_node;


	if (*pipe_iter <= pipe_fd->size / 2)
	{
		ast_node = ft_ast_left_most(tree->left);
		if (ast_node)
		{
			ft_execut_command(ft_ast_to_command(ast_node), env, function_table, pipe_fd, *pipe_iter);
			(*pipe_iter)++;
		}

		ft_execut_command(ft_ast_to_command(tree->right), env, function_table, pipe_fd, *pipe_iter);
		(*pipe_iter)++;
	}
	
	return(0);
}	

// TODO: open wait for process and close unclosd fd
void	ft_execute_part(t_ast_node *tree, t_hash_table *env, t_hash_table *func_table, t_vector *pipe_fd, size_t* pipe_iter)
{
	if (!tree)
		return ;

	ft_execute_part(tree->left, env, func_table, pipe_fd, pipe_iter);
	
	if (tree->token_type == PIPE)
	{
		ft_open_process_for_pipe(tree, env, func_table, pipe_fd, pipe_iter);
		return;
	}
	ft_execute_part(tree->right, env, func_table, pipe_fd, pipe_iter);
}







// void	ft_open_proces(size_t pipe_count)
// {
	
// }

// void	ft_open_wait(size_t pipe_count)
// {
	
// }