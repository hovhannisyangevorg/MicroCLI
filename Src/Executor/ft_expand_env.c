/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:24:26 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/12 19:27:04 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"


int ft_variable_identifier(char *ident);


int ft_ignore_symbol(char *str, char sym, size_t i)
{
	if (str && str[i])
	{
		++i;
		while (str[i] && str[i] != sym && !ft_isspace(str[i]))
			++i;
	}
	return (i);
}

size_t ft_size_variable_$(char *arg, t_symbol_table *symbol_table)
{
	size_t	i;
	size_t	size;
	size_t 	start;
	char 	*for_rep;
	int		end;

	i 		= 0;
	start  	= 0;
	size 	= 0;
	while (arg && arg[i])
	{
		if (arg[i] == '$')
		{
			start 		= i;
			end 		= ft_ignore_symbol(arg, '$', i);
			++i;
			if (arg[i] == '$')
			{
				size += ft_strlen(ft_get_env(symbol_table->env, "$"));
				++i;
				continue ;
			}
			for_rep 	= ft_substr(arg, i, (end - i));
			if (ft_variable_identifier(for_rep))
			{
				size 		+= ft_strlen(ft_get_env(symbol_table->env, for_rep));
			}
			else
				size += end - start;
			i = end;
			continue ; 
		}
		++size;
		i++;
	}
	return (size);
}










size_t ft_count_replace_len(char *arg, t_symbol_table *symbol_table)
{
	int 	i;
	int 	index_quot;
	char	*for_rep;
	size_t 	size;

	i 		= 0;
	size 	= 0;
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			index_quot = ft_ignore_quots(arg, arg[i], i);
			if (arg[i] == '\'')
				size += index_quot - i;
			else
			{
				++i;
				for_rep 	= ft_substr(arg, i, (index_quot - i));
				size 		+= ft_size_variable_$(for_rep, symbol_table);
				free(for_rep);
			}
			i 	= index_quot;
			continue ;
		} else if (arg[i] == '$')
		{
			index_quot	= ft_ignore_symbol(arg, arg[i], i);
			++i;
			if (arg[i] && arg[i] == '$')
			{
				size += ft_strlen(ft_get_env(symbol_table->env, "$"));
				++i;
				continue ;
			}
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
	size_t	size;
	char 	*for_rep;
	int		end;

	i 		= 0;
	size 	= 0;
	printf("env:--------->%s\n", arg);
	while (arg && arg[i])
	{
		if (arg[i] == '$')
		{
			end 		= ft_ignore_symbol(arg, '$', i);
			++i;
			if (arg[i] == '$')
			{
				size_t len = ft_strlen(ft_get_env(symbol_table->env, "$"));
				// printf("sssL: %lu\n", size);
				// ft_memmove(expand + size, ft_get_env(symbol_table->env, "$"), len);
				ft_strlcat(expand + size, ft_get_env(symbol_table->env, "$"), len);

				size += len;
				++i;
				continue ;
			}
			
			for_rep 	= ft_substr(arg, i, (end - i));
			// printf("sub: %s\n", for_rep);
			if (ft_variable_identifier(for_rep))
			{
				size_t len = ft_strlen(ft_get_env(symbol_table->env, for_rep));
				// printf("sssL: %lu\n", size);
				ft_strlcat(expand + size, ft_get_env(symbol_table->env, for_rep), len);
				// memmove(expand + size, ft_get_env(symbol_table->env, for_rep), len + 1);
				size 		+= len;
			} else
			{
				expand[size] = '$';
				++size;
				// ft_memmove(expand + size, for_rep, end - i);
				ft_strlcat(expand + size, for_rep, end - i);
				size += end - i;
			}
			i = end;
			free(for_rep);
			continue ; 
		}

		expand[size] = arg[i];
		++size;
		i++;
	}
	return (size);
}





int ft_variable_identifier(char *ident)
{
	int i;

	i = 0;
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



char* ft_count_replace(char *arg, t_symbol_table *symbol_table)
{
	int 	i;
	int 	index_quot;
	char	*for_rep;
	size_t j;

	i 		= 0;
	j		= 0;
	char	*expand = ft_calloc(ft_count_replace_len(arg, symbol_table) + 1, sizeof(char)); 
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			index_quot = ft_ignore_quots(arg, arg[i], i);
			if (arg[i] == '\'')
			{
				if (!arg[++i])
					continue;
				ft_memmove(expand + j, (arg + i), index_quot - i);
				j += index_quot - i;
			}
			else
			{
				++i;
				for_rep 	= ft_substr(arg, i, (index_quot - i));
				j 			+= ft_vulue_variable_$(for_rep, expand + j ,symbol_table);
				free(for_rep);
			}
			i 	= index_quot;
			continue ;
		} else if (arg[i] == '$')
		{
			index_quot	= ft_ignore_symbol(arg, arg[i], i);	
			printf("next: %d %lu\n", index_quot, j);
			for_rep 	= ft_substr(arg, i, (index_quot - i));
			j 			+= ft_vulue_variable_$(for_rep, expand + j ,symbol_table);
			free(for_rep);
			i 	= index_quot;
			continue ;
		}
		expand[j] = arg[i];
		j++;
		i++;
	}
	return (expand);
}


























