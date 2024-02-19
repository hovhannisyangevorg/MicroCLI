/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:28:23 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 19:03:26 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_isquot(const char *end_of_file)
{
	if ((end_of_file && *end_of_file) && (ft_strchr((char *)end_of_file, '\"') || ft_strchr((char *)end_of_file, '\'')))
		return (1);
	else
		return (0);
}

char *ft_generate_filename()
{
	static size_t	i;
	char 			*id;
	char			*filename;

	filename	= ft_strdup(HEREDOC_DIR"/.heredoc");
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

int open_heredoc(t_redirect	*red, t_hash_table *env)
{
	// (void)io;
	int 	here_fd;
	int		flag;
	char	*line;
	char	*filename;
	char	*end_of_file;
	
	flag 		= 0;
	filename	= ft_generate_filename();
	here_fd 	= open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	end_of_file = ft_ignor_EOF_quots(red->argument);

	signal(SIGINT, ft_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
	g_global_state.minishell_signal = SIGHEREDOC;
	if (ft_isquot(red->argument))
		flag = 1;
	int stdio 	= dup(STDIN_FILENO);
	
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, end_of_file))
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);
			break ;
		}
		if (!flag)
			ft_hendle_env_variable(&line, env);
		ft_putstr_fd(line, here_fd);
		ft_putstr_fd("\n", here_fd);
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global_state.orig_termios);
	close(here_fd);
	if (g_global_state.heredoc_signal == -1)
	{
		here_fd 	= open(filename,  O_RDONLY, 0666);
	}
	else
		here_fd = -1;
	dup2(stdio, STDIN_FILENO);
	close(stdio);
	free(end_of_file);
	unlink(filename);
	free(filename);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	return (here_fd);
}