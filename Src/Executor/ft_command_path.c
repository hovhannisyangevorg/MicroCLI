/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:28:01 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 18:39:12 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/**
 * Src/Executor/ft_command_path.c
 */
int		ft_command_path(t_command *command, t_hash_table *env);


int ft_is_dir(char* path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			g_global_state.is_dir = 1;
			g_global_state.permission_status = 0;
			return errno;
		}
		return 0;
	}
	else
		return errno;
}

int ft_find_from_env(char** path, char* path_exec, t_hash_table* env)
{
	int			status;
	char		**paths;
	char		*prefix;
	size_t		i;


	prefix		= NULL;
	i 			= 0;
	status = EXIT_SUCCESS;
	paths = ft_split(ft_get_env(env, "PATH"), ':');
	while (paths[i])
	{
		prefix = ft_strdup(paths[i]);
		prefix = ft_gnl_strjoin(prefix, "/");
		prefix = ft_gnl_strjoin(prefix, path_exec);
		status = access(prefix, F_OK | X_OK);
		if (!status)
		{
			free(*path);
			*path = prefix;
			status = EXIT_SUCCESS;
			break;
		}
		i++;
	}
	ft_vecstrdel(&paths);
	return status;
} 

int ft_is_relative_or_abs(char* path, char* path_exec)
{
	int status;

	status = EXIT_SUCCESS;
	if (ft_is_dir(path))
			return (errno);
	status = access (path_exec, F_OK);

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

int ft_command_path(t_command *command, t_hash_table *env)
{
	char		*path_exec;
	int			status;
	
	status		= EXIT_SUCCESS;
	path_exec 	= ft_strdup(command->argument->arguments[0]);
	if (path_exec[0] == '/')
		return ft_is_relative_or_abs(command->argument->arguments[0], path_exec + 1);
	else if (!ft_strncmp(path_exec, "./", 2))
		return ft_is_relative_or_abs(command->argument->arguments[0], path_exec + 2);
	else if (!ft_strncmp(path_exec, "../", 3))
		return ft_is_relative_or_abs(command->argument->arguments[0], path_exec + 3);
	else
		status = ft_find_from_env(&command->argument->arguments[0], path_exec, env);
	free(path_exec);
    if (ft_is_dir(command->argument->arguments[0]))
		return errno;
	if (status)
	{
		g_global_state.permission_status = errno;
		return (errno);
	}
	return EXIT_SUCCESS;
}