/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:24:26 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/14 23:19:08 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"


int ft_variable_identifier(char *ident);


int ft_ignore_symbol(char *str, char sym, size_t i)
{
	if (str && str[i])
	{
		++i;
		if (str[i] == '?')
			return i;
		while (str[i] && str[i] != sym && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '\"' && str[i] != '/')
			++i;
	}
	return (i);
}

size_t ft_size_variable_$(char *arg, t_symbol_table *symbol_table)
{
	size_t	i;
	size_t	len;

	i 		= 0;
	size_t start = 0;

	len = 0;

	if (arg[i] == '$')
	{
		start = i;
		++i;
		if (arg[i] == '$')
		{
			len = ft_strlen(ft_get_env(symbol_table->env, "$"));
			return len;
		}
		else if (arg[i] == '?')
		{
			len = ft_strlen(ft_get_env(symbol_table->env, "?"));
			return len;
		}
		if (ft_variable_identifier(arg + start))
		{
			len = ft_strlen(ft_get_env(symbol_table->env, arg + i));
			return len;
		}
		else
		{
			return ft_strlen(arg + start);
		}
		
	}
	return 0;
}


size_t ft_count_replace_len(char *arg, t_symbol_table *symbol_table, t_expand_type isexpand)
{
	int 	i;
	int 	index_quot;
	char	*for_rep;
	size_t 	size;

	i 		= 0;
	size 	= 0;
	while (arg && arg[i])
	{
		if (isexpand && (arg[i] == '\'' || arg[i] == '\"'))
		{
			index_quot = ft_ignore_quots(arg, arg[i], i);
			if (arg[i] == '\'')
			{
				size += index_quot - i - 1;
				i 	= index_quot + 1;
			}
			else
			{
				++i;
				for_rep 	= ft_substr(arg, i, (index_quot - i));
				size 		+= ft_count_replace_len(for_rep, symbol_table, EXPAND);
				free(for_rep);
				i 	= index_quot + 1;
			}
			continue ;
		} else if (arg[i] == '$')
		{
			index_quot	= ft_ignore_symbol(arg, arg[i], i);
			if (arg[i + 1] == '$')
			{
				for_rep 	= ft_strdup("$$");
				index_quot++;
			}
			else if (arg[i + 1] == '?')
			{
				for_rep 	= ft_strdup("$?");
				index_quot++;
			}
			else
				for_rep 	= ft_substr(arg, i, (index_quot - i));
			size 		+= ft_size_variable_$(for_rep, symbol_table);
			free(for_rep);
			i 	= index_quot;
			continue ;
		}
		size++;
		i++;
	}
	return (size);
}













size_t ft_vulue_variable_$(char *arg, char *expand, t_symbol_table *symbol_table)
{
	size_t	i;
	size_t	len;
	i 		= 0;
	size_t start = 0;

	len = 0;

	if (arg[i] == '$')
	{
		start = i;
		++i;
		if (arg[i] == '$')
		{
			len = ft_strlen(ft_get_env(symbol_table->env, "$"));
			ft_memmove(expand, ft_get_env(symbol_table->env, "$"), len);
			return len;
		}
		else if (arg[i] == '?')
		{
			len = ft_strlen(ft_get_env(symbol_table->env, "?"));
			ft_memmove(expand, ft_get_env(symbol_table->env, "?"), len);
			return len;
		}
		if (ft_variable_identifier(arg + start))
		{
			len = ft_strlen(ft_get_env(symbol_table->env, arg + i));
			ft_memmove(expand, ft_get_env(symbol_table->env, arg + i), len);
			return len;
		}
		else
		{
			len = ft_strlen(arg + start);
			ft_memmove(expand, arg + start, len);
			return len;
		}
		
	}
	return 0;
}

int ft_variable_identifier(char *ident)
{
	int i;

	i = 1;
	if (!ident[i] || ident[i] == '\"' || ident[i] == '\'')
		return 0;
	if (ft_isdigit(ident[i]))
		return (0);
	while (ident && ident[i])
	{
		if (!(ft_isalnum(ident[i]) || ident[i] == '_'))
			return (0);
		++i;
	}
	return (1);
}



char* ft_count_replace(char *arg, t_symbol_table *symbol_table, t_expand_type isexpand)
{
	int 	i;
	int 	index_quot;
	size_t 	start;
	char	*expand;
	char	*for_rep;

	i 		= 0;
	start	= 0;
	expand = ft_calloc(ft_count_replace_len(arg, symbol_table, isexpand) + 1, sizeof(char)); 
	while (arg && arg[i])
	{
		if (isexpand && (arg[i] == '\'' || arg[i] == '\"'))
		{

			index_quot = ft_ignore_quots(arg, arg[i], i);
			
			if (arg[i] == '\'')
			{
				ft_memmove(expand + start, (arg + i + 1), index_quot - i - 1);
				start += index_quot - i - 1;
				i 	= index_quot + 1;
			}
			else
			{
				++i;
				for_rep 	= ft_substr(arg, i, (index_quot - i));
				char* tmp = ft_count_replace(for_rep, symbol_table, EXPAND);
				size_t len = ft_strlen(tmp);
				ft_memmove(expand + start, tmp, len);
				free(tmp);
				start += len;
				free(for_rep);
				i 	= index_quot + 1;
			}
			continue ;
		}
		else if (arg[i] == '$')
		{
			index_quot	= ft_ignore_symbol(arg, arg[i], i);
			if (arg[i + 1] == '$')
			{
				for_rep 	= ft_strdup("$$");
				index_quot++;
			}
			else if (arg[i + 1] == '?')
			{
				for_rep 	= ft_strdup("$?");
				++index_quot;
			}
			else
				for_rep 	= ft_substr(arg, i, (index_quot - i));
			
			start		+= ft_vulue_variable_$(for_rep, expand + start ,symbol_table);
			free(for_rep);
			i 	= index_quot;
			continue ;
		}
		expand[start] = arg[i];
		start++;
		i++;
	}
	expand[start] = '\0';
	return (expand);
}


























