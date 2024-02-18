/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:58:30 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/14 15:32:16 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

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



void ft_hendle_pipe(t_vector * pipe_fd, size_t pipe_iter, t_io io)
{
	size_t i;

	i = 0;
	if (pipe_iter != 0 && io.input == STDIN_FILENO)
		dup2(pipe_fd->arr[(pipe_iter - 1) * 2], STDIN_FILENO);
	if (pipe_iter != pipe_fd->size / 2 && io.output == STDOUT_FILENO)
		dup2(pipe_fd->arr[(pipe_iter * 2) + 1], STDOUT_FILENO);
	while (i < pipe_fd->size)
		close(pipe_fd->arr[i++]);
}



int ft_command_fron_PATH(t_command *command, t_hash_table *env)
{
	size_t i;
	char **paths;
	struct stat path_stat;
	char *path_exec;
	char *prefix;
	int	 status;
	
	i 		= 0;
	status	= EXIT_SUCCESS;
	prefix	= NULL;
	path_exec = ft_strdup(command->argument->arguments[0]);
	
	if (path_exec[0] == '/' || !ft_strncmp(path_exec, "./", 2) || !ft_strncmp(path_exec, "../", 3))
	{
		if (stat(command->argument->arguments[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				g_global_state.is_dir = 1;
				g_global_state.permission_status = 0;
				return errno;
			}
		}

		status = access (path_exec, F_OK);
		free(path_exec);
		path_exec = NULL;

		if (status == -1)
		{
			g_global_state.permission_status = errno;
			return errno;
		}
		status = access (path_exec, X_OK);
		if (status == -1)
		{
			g_global_state.permission_status = errno;
			return errno;
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		
		paths = ft_split(ft_get_env(env, "PATH"), ':');
		while (paths[i])
		{
			prefix = ft_strdup(paths[i]);
			prefix = ft_gnl_strjoin(prefix, "/");
			prefix = ft_gnl_strjoin(prefix, path_exec);
			status = access(prefix, F_OK | X_OK);
			if (!status)
			{
				free(command->argument->arguments[0]);
				command->argument->arguments[0] = prefix;
				status = EXIT_SUCCESS;
				break;
			}
			i++;
		}
		ft_vecstrdel(&paths);
		
	}

	free(path_exec);

    // Get information about the file
    if (stat(command->argument->arguments[0], &path_stat) == 0)
	{
        if (S_ISDIR(path_stat.st_mode))
		{
			g_global_state.is_dir = 1;
			g_global_state.permission_status = 0;
			return errno;
		}
	}
	if (status)
	{
		g_global_state.permission_status = errno;
		return (errno);
	}
	return EXIT_SUCCESS;
}

void ft_handle_redirect_ios(t_io io)
{
	if (io.input != STDIN_FILENO)
	{
		// printf("fd: %d\n", io.input);
		dup2(io.input, STDIN_FILENO);
		close(io.input);
	}
	if (io.output != STDOUT_FILENO)
	{
		dup2(io.output, STDOUT_FILENO);
		close(io.output);
	}
	if (io.error != STDERR_FILENO)
	{
		dup2(io.error, STDERR_FILENO);
		close(io.error);
	}
}

void ft_expand_env(t_command *command, t_symbol_table* table)
{
	size_t i = 0;
	if (command->argument && command->argument->arguments && command->argument->arguments[0])
	{
		while (command->argument && command->argument->arguments && command->argument->arguments[i])
		{
			char* tmp = ft_count_replace(command->argument->arguments[i], table, NOEXPAND);
			free(command->argument->arguments[i]);
			command->argument->arguments[i] = tmp;
			++i;
		}
		i = 0;
		size_t j = 0;
		while (command->argument && command->argument->arguments && command->argument->arguments[i])
		{
			if (ft_strlen(command->argument->arguments[i]))
				++j;
				// printf("arg: %s\n", command->argument->arguments[i]);
			++i;
		}
		char** av = ft_calloc(j + 1, sizeof(char*));
		j = 0;
		i = 0;
		while (command->argument && command->argument->arguments && command->argument->arguments[i])
		{
			if (ft_strlen(command->argument->arguments[i]))
			{
				av[j] = ft_strdup(command->argument->arguments[i]);
				++j;
			}
				// printf("arg: %s\n", command->argument->arguments[i]);
			++i;
		}
		command->argument->arguments = av;
		// i = 0;
		// while (av && av[i])
		// {
			
		// 	// printf("arg %s\n", av[i]);
		// 		// printf("arg: %s\n", command->argument->arguments[i]);
		// 	++i;
		// }

	}
	
}


char	*ft_get_last_arg(t_command* command)
{
	if (!command || !command->argument || !command->argument->arguments || !command->argument->arguments[0])
		return NULL;
	size_t i = 0;
	while (command->argument->arguments[i])
		++i;
	return ft_strdup(command->argument->arguments[i - 1]);
}

int		ft_execut_command(t_io io, t_command *command, t_symbol_table* table, t_vector *pipe_fd, size_t pipe_iter)
{
	t_function_callback biltin_func;
	t_hash_table_arr env;
	t_vector fd_vector;
	int status;

	status = 0;
	g_global_state.is_dir = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);
	signal(SIGINT, SIG_IGN);
	g_global_state.permission_status = SUCCESS_CODE;
	env = ft_convert_env_to_args(table->env, 1, 0);
	ft_expand_env(command, table);

	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0) 
	{
		rl_catch_signals = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		g_global_state.permission_status = 0;
		ft_init_arrey(&fd_vector, 0);
		ft_open_file(command, table->env, &fd_vector, io);

		ft_handle_redirect_ios(command->io);
		ft_hendle_pipe(pipe_fd, pipe_iter, command->io);
		if (!command->argument->arguments)
			biltin_func = NULL;
		else
			biltin_func =  ft_get_function(table->function, command->argument->arguments[0]);
		if (biltin_func)
		{
			int status = biltin_func(command, table);
			exit(status);
		}
		else if (command->argument && command->argument->arguments && command->argument->arguments[0])
		{

			status = ft_command_fron_PATH(command, table->env);
			if (g_global_state.is_dir)
			{
				ft_putstr_fd("Minishell: ", STDERR_FILENO);
				ft_panic_shell(command->argument->arguments[0], " Is a directory");
				exit(g_global_state.permission_status);
			}
			if (g_global_state.permission_status)
			{
				ft_panic_shell("minishell: ", strerror(g_global_state.permission_status));
				exit(g_global_state.permission_status);
			}
			if (!status)
				execve(command->argument->arguments[0], command->argument->arguments, env.table);
			else if (status != 126)
				ft_panic_shell(command->argument->arguments[0], ": command not found");
			exit(status);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (command->base.parent && command->base.parent->parent && command->base.parent->parent->token_type != ROOT)
			ft_restore_std_io(io);

	}
	return(0);
}


int		ft_open_process_for_pipe(t_io io, t_ast_node *tree, t_symbol_table* table, t_vector *pipe_fd, size_t* pipe_iter)
{
	t_ast_node *ast_node;


	if (*pipe_iter <= pipe_fd->size / 2)
	{
		ast_node = ft_ast_left_most(tree->left);
		if (ast_node)
		{

			ft_execut_command(io, ft_ast_to_command(ast_node), table, pipe_fd, *pipe_iter);
			g_global_state.argument = ft_get_last_arg(ft_ast_to_command(ast_node));
			(*pipe_iter)++;
		}
		ft_execut_command(io, ft_ast_to_command(tree->right), table, pipe_fd, *pipe_iter);
		g_global_state.argument = ft_get_last_arg(ft_ast_to_command(tree->right));
		(*pipe_iter)++;
	}
	
	return(0);
}	

// TODO: open wait for process and close unclosd fd
void	ft_execute_part(t_io io, t_ast_node *tree, t_symbol_table* table, t_vector *pipe_fd, size_t* pipe_iter)
{
	if (!tree)
		return ;

	ft_execute_part(io, tree->left, table, pipe_fd, pipe_iter);
	
	if (tree->token_type == PIPE)
	{
		ft_open_process_for_pipe(io, tree, table, pipe_fd, pipe_iter);
		return ;
	}
	ft_execute_part(io, tree->right, table, pipe_fd, pipe_iter);
}