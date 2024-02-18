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

int ft_command_path(t_command *command, t_hash_table *env)
{
	size_t		i;
	char		**paths;
	struct stat path_stat;
	char		*path_exec;
	char		*prefix;
	int			status;
	
	i 			= 0;
	status		= EXIT_SUCCESS;
	prefix		= NULL;
	path_exec 	= ft_strdup(command->argument->arguments[0]);
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