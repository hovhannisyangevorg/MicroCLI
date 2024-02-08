/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:21:12 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/04 19:59:54 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	ft_pipe_count_tree(t_ast_node *tree)
{
	size_t count_left	= 0;
	size_t count_right	= 0;
	if (!tree)
		return (0);
	if (tree->token_type == PIPE)
	{
		count_left	= ft_pipe_count_tree(tree->left);
		count_right	= ft_pipe_count_tree(tree->right);
		return (count_left + count_right + 1);
	}
	count_left 	= ft_pipe_count_tree(tree->left);
	count_right = ft_pipe_count_tree(tree->right);
	return (count_left + count_right);
}

void ft_replace_all(char **line, char *src_env, char *chang_env)
{
	size_t	token_size;
	char	*token_tmp;
	char	*start_offset;
	char	*end_offset;
	
	token_size	= ft_strlen(src_env); 
	start_offset	= ft_strdup(*line);
	token_tmp	= ft_strstr(start_offset, src_env);
	while (token_tmp)
	{
		if (token_size)
		{
			end_offset = ft_strdup(token_tmp + token_size);
			if (!end_offset)
				end_offset = ft_strdup("");
			start_offset = ft_substr(start_offset, 0, token_tmp - start_offset);
			start_offset = ft_gnl_strjoin(start_offset, chang_env);
			start_offset = ft_gnl_strjoin(start_offset, end_offset);
			free(end_offset);
		}
		if (*token_tmp)
			token_tmp = ft_strstr(start_offset, src_env);
		else
			token_tmp = NULL;
	}
	free(*line);
	*line = start_offset;
}

char	*ft_substr_c(char *line, char c)
{
	size_t i = 0;
	size_t start = 0;
	while (line && line[i] && line[i] != c)
		++i;
	start = i;
	if (line[i])
		++i;
	while (line && line[i] && line[i] != c && !ft_isspace(line[i]) && line[i] != '\'' && line[i] != '\"')
		++i;
	return (ft_substr(line, start, i - start));
}

void	ft_hendle_env_variable(char **line, t_hash_table *env)
{
	char	dellim;
	char	*start_env;
	char	*token_env;
	char	*value;

	dellim		= '$';
	token_env	= NULL;
	start_env	= ft_strchr(*line, dellim);
	while(start_env)
	{
		token_env = ft_substr_c(start_env, dellim);
		if (!*token_env)
			value = ft_get_env(env, token_env);
		else
			value = ft_get_env(env, token_env + 1);
		if (value)
			ft_replace_all(line, token_env, value);
		if (*start_env)
			start_env = ft_strchr(start_env + 1, dellim);
		else
			start_env = NULL;
	}
	
}

int	ft_isquot(const char *end_of_file)
{
	if (end_of_file && *end_of_file && ft_strchr((char *)end_of_file, '\"') && ft_strchr((char *)end_of_file, '\''))
		return (1);
	else
		return (0);
}

size_t	ft_EOF_length(char *end_of_file)
{
	size_t	i;
	size_t	eof_size;
	char	crrent;

	i			= 0;
	eof_size	= 0;

	while (end_of_file && end_of_file[i])
	{
		if (end_of_file[i] == '\'' || end_of_file[i] == '\"')
		{
			crrent =  end_of_file[i++];
			while (end_of_file[i] != crrent)
			{
				++eof_size;
				++i;
			}
			if (end_of_file[i] == '\'' || end_of_file[i] == '\"')
				i++;
			continue ;
		}
		++eof_size;
		i++;
	}
	return (eof_size);
}

char *ft_ignor_EOF_quots(char *end_of_file)
{
	size_t	i;
	size_t  j;
	size_t	eof_size;
	char	crrent;
	char 	*eof_key;

	i			= 0;
	j			= 0;
	eof_size	= 0;
	eof_size	= ft_EOF_length(end_of_file);
	eof_key		= (char *)malloc(sizeof(char) * (eof_size + 1));
	if (!eof_key)
		return (NULL);

	while (end_of_file && end_of_file[i])
	{
		if (end_of_file[i] == '\'' || end_of_file[i] == '\"')
		{
			crrent =  end_of_file[i++];
			while (end_of_file[i] != crrent)
			{
				eof_key[j++] = end_of_file[i++];
			}
			if (end_of_file[i] == '\'' || end_of_file[i] == '\"')
				i++;
			continue ;
		}
		eof_key[j++] = end_of_file[i];
		i++;
	}
	eof_key[j++] = '\0';
	return (eof_key);
}

char *ft_generate_filename()
{
	static size_t	i;
	char 			*id;
	char			*filename;

	filename	= ft_strdup("/tmp/.heredoc");
	if (i == 0)
	{
		i++;	
		return (filename);
	}
	id			= ft_itoa(i++);
	filename	= ft_gnl_strjoin(filename, id);
	free(id);
	return (filename);
}


int open_heredoc(t_redirect	*red, t_hash_table *env)
{
	int 	fd;
	int		flag;
	char	*line;
	char	*filename;
	char	*end_of_file;
	
	flag 		= 0;
	filename	= ft_generate_filename();
	fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0664);
	end_of_file = ft_ignor_EOF_quots(red->argument);
	if (ft_isquot(red->argument))
		flag = 1;
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, end_of_file))
			break ;
		if (!flag)
			ft_hendle_env_variable(&line, env);
		printf ("%s\n", line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(end_of_file);
	free(filename);
	return (fd);
}


void	ft_open_type(t_redirect *redirect, t_command *cmd, t_vector *fd_vector, t_hash_table *env)
{
	int fd;

	fd = -1;
	if (redirect->base.token_type == WRITE)
	{
		fd = open(redirect->argument, O_TRUNC | O_WRONLY | O_CREAT, 0664);
		if (cmd->io.output < fd)
			cmd->io.output = fd;
		else
			ft_push_arrey(fd_vector, fd);
	}
	else if (redirect->base.token_type == READ)
	{
		fd = open(redirect->argument,  O_RDONLY);
		if (cmd->io.input < fd)
			cmd->io.input = fd;
		else
			ft_push_arrey(fd_vector, fd);
	}
	else if (redirect->base.token_type == APPEND)
	{
		fd = open(redirect->argument, O_APPEND | O_WRONLY | O_CREAT);
		if (cmd->io.output < fd)
			cmd->io.output = fd;
		else
			ft_push_arrey(fd_vector, fd);
	}
	else if (redirect->base.token_type == HEREDOC)
	{
		fd = open_heredoc(redirect, env);
		if (cmd->io.input < fd)
			cmd->io.input = fd;
		else
			ft_push_arrey(fd_vector, fd);
	}
}

void ft_close_fd(t_vector *fd_vector)
{
	size_t i;

	i = 0;
	while (i < fd_vector->size)
		close(fd_vector->arr[i++]);
	free(fd_vector->arr);
}

void	ft_open_all_fd(t_ast_node *ast_node, t_hash_table *env)
{
	t_command	*command;
	t_ast_node	*node;
	t_vector fd_vector;
	if (!ast_node)
		return ;
	ft_init_arrey(&fd_vector, 0);
	if (ast_node->token_type == COMMAND)
	{
		command		= ft_ast_to_command(ast_node);
		node		= ft_redirect_to_ast_node(command->redirect);
		while (node)
		{
			ft_open_type(ft_ast_to_redirect(node), command, &fd_vector, env);
			node = node->left;
		}
		ft_close_fd(&fd_vector);
	}
	ft_open_all_fd(ast_node->left, env);
	ft_open_all_fd(ast_node->right, env);
}

// TODO expand env in command argument 
void ft_executor(t_hash_table *table_env, t_container cont)
{
	t_vector	pipe_fd;
	size_t 		pipe_count;
	size_t		pipe_iter;


	if (cont.exec_type == LIST)
	{
		pipe_count = 0;
	}
	else
	{
		pipe_count = ft_pipe_count_tree(cont.tree->ast_node);
		ft_open_all_fd(cont.tree->ast_node, table_env);
		pipe_fd = ft_open_pipe_fd(pipe_count);
		pipe_iter = 0;
		
		char *leak = ft_strdup("");
		ft_ast_print(cont.tree->ast_node, leak, 0, 1);
		free(leak);
		
		ft_execute_part(cont.tree->ast_node, table_env, &pipe_fd, &pipe_iter);
		
		for (size_t i = 0; i < pipe_fd.size; i++)
		{
			close(pipe_fd.arr[i]);
		}
		for (size_t i = 0; i < pipe_count + 1; i++)
		{
			wait(NULL);
			// close(pipe_fd.arr[i]);
		}
		
		
		
		
		// ft_assign_pipe_fd(cont.tree->ast_node->left, &pipe_fd, &pipe_iter);



		ft_free_tree(cont.tree->ast_node);	
		free(cont.tree);
		// printf("aaaaaa\n");
	}
	
	(void)pipe_count;
	// print_env(table_env);
}
