/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:24:26 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 18:49:30 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

int ft_ignore_symbol(char *str, char sym, size_t i)
{
	if (str && str[i])
	{
		++i;
		if (str[i] == '?')
			return i;
		while (str[i] && str[i] != sym && !ft_isspace(str[i]) && \
			str[i] != '\'' && str[i] != '\"' && str[i] != '/')
			++i;
	}
	return (i);
}

size_t ft_get_length(char *arg, size_t i, size_t start, t_symbol_table* table)
{
	if (arg[i] == '$')
		return ft_strlen(ft_get_env(table->env, "$"));
	else if (arg[i] == '?')
		return ft_strlen(ft_get_env(table->env, "?"));
	if (ft_variable_identifier(arg + start))
		return ft_strlen(ft_get_env(table->env, arg + i));
	return ft_strlen(arg + start);
}

size_t ft_size_variable_$(char *arg, t_symbol_table *symbol_table)
{
	size_t	i;
	size_t	start;
	
	start	= 0;
	i		= 0;
	if (arg[i] == '$')
	{
		start = i;
		++i;
		return ft_get_length(arg, i, start, symbol_table);
	}
	return (0);
}

char	*ft_get_pattern(char* arg, size_t i, size_t *index_quot)
{
	char* for_rep;

	if (arg[i + 1] == '$')
	{
		for_rep 	= ft_strdup("$$");
		++(*index_quot);
	}
	else if (arg[i + 1] == '?')
	{
		for_rep 	= ft_strdup("$?");
		++(*index_quot);
	}
	else
		for_rep 	= ft_substr(arg, i, (*index_quot - i));
	return (for_rep);
}

size_t ft_copy_pattern(t_expand_token expand, t_symbol_table	*table, size_t start)
{
	if (expand.token[expand.index] == '$')
	{
		expand.size = ft_strlen(ft_get_env(table->env, "$"));
		ft_memmove(expand.for_rep, ft_get_env(table->env, "$"), expand.size);
		return expand.size;
	}
	else if (expand.token[expand.index] == '?')
	{
		expand.size = ft_strlen(ft_get_env(table->env, "?"));
		ft_memmove(expand.for_rep, ft_get_env(table->env, "?"), expand.size);
		return expand.size;
	}
	if (ft_variable_identifier(expand.token + start))
	{
		expand.size = ft_strlen(ft_get_env(table->env, expand.token + expand.index));
		ft_memmove(expand.for_rep, ft_get_env(table->env, expand.token + expand.index), expand.size);
		return expand.size;
	}
	expand.size = ft_strlen(expand.token + start);
	ft_memmove(expand.for_rep, expand.token + start, expand.size);
	return expand.size;
}

void ft_handle_exp_quotes(t_expand_token* exp, t_symbol_table* table)
{
	exp->index_quot = ft_ignore_quots(exp->token, exp->token[exp->index], exp->index);
	if (exp->token[exp->index] == '\'')
	{
		exp->size += exp->index_quot - exp->index - 1;
		exp->index = exp->index_quot + 1;
	}
	else
	{
		++exp->index;
		exp->for_rep 	= ft_substr(exp->token, exp->index, (exp->index_quot - exp->index));
		exp->size 	+= ft_count_replace_len(exp->for_rep, table, EXPAND);
		free(exp->for_rep);
		exp->index = exp->index_quot + 1;
	}
}

size_t ft_count_replace_len(char *arg, t_symbol_table *symbol_table, t_expand_type isexpand)
{
	t_expand_token expand;

	expand.index 	= 0;
	expand.size 	= 0;
	expand.token = arg;
	while (expand.token && expand.token[expand.index])
	{
		if (isexpand && (expand.token[expand.index] == '\'' || expand.token[expand.index] == '\"'))
		{
			ft_handle_exp_quotes(&expand, symbol_table);
			continue ;
		}
		else if (expand.token[expand.index] == '$')
		{
			expand.index_quot	= ft_ignore_symbol(expand.token, expand.token[expand.index], expand.index);
			expand.for_rep		= ft_get_pattern(expand.token, expand.index, &expand.index_quot);
			expand.size 		+= ft_size_variable_$(expand.for_rep, symbol_table);
			free(expand.for_rep);
			expand.index 	= expand.index_quot;
			continue ;
		}
		++expand.size;
		++expand.index;
	}
	return (expand.size);
}

size_t ft_vulue_variable_$(char *arg, char *expand, t_symbol_table *symbol_table)
{
	t_expand_token exp;
	size_t	i;
	size_t	len;
	size_t start;
	
	start	= 0;
	len		= 0;
	i 		= 0;
	exp.token = arg;
	exp.for_rep = expand;
	if (arg[i] == '$')
	{
		start = i;
		++i;
		exp.index = i;
		exp.size = len;
		return ft_copy_pattern(exp, symbol_table, start);
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

void ft_replace_pattern(char *expand, t_expand_token* exp, t_symbol_table* table)
{
	char	*tmp;
	size_t	len;

	tmp = NULL;
	len = 0;
	exp->index_quot = ft_ignore_quots(exp->token, exp->token[exp->index], exp->index);
			
	if (exp->token[exp->index] == '\'')
	{
		ft_memmove(expand + exp->size, (exp->token + exp->index + 1), exp->index_quot - exp->index - 1);
		exp->size += exp->index_quot - exp->index - 1;
		exp->index 	= exp->index_quot + 1;
	}
	else
	{
		++exp->index;
		exp->for_rep 	= ft_substr(exp->token, exp->index, (exp->index_quot - exp->index));
		tmp = ft_count_replace(exp->for_rep, table, EXPAND);
		len = ft_strlen(tmp);
		ft_memmove(expand + exp->size, tmp, len);
		free(tmp);
		exp->size += len;
		free(exp->for_rep);
		exp->index 	= exp->index_quot + 1;
	}
}

int ft_handle_replace_exp(char *expand, t_symbol_table* table, t_expand_token* exp, t_expand_type isexpand)
{
	if (isexpand && (exp->token[exp->index] == '\'' || exp->token[exp->index] == '\"'))
	{
		ft_replace_pattern(expand, exp, table);
		return (1);
	}
	else if (exp->token[exp->index] == '$')
	{
		exp->index_quot	= ft_ignore_symbol(exp->token, exp->token[exp->index], exp->index);
		exp->for_rep = ft_get_pattern(exp->token, exp->index, &exp->index_quot);
		exp->size		+= ft_vulue_variable_$(exp->for_rep, expand + exp->size, table);
		free(exp->for_rep);
		exp->index 	= exp->index_quot;
		return (1);
	}
	return (0);
}

char* ft_count_replace(char *arg, t_symbol_table *table, t_expand_type isexpand)
{
	t_expand_token	exp;
	char			*expand;

	exp.token = arg;
	exp.size = 0;
	exp.index = 0;
	exp.index_quot = 0;
	expand = ft_calloc(ft_count_replace_len(arg, table, isexpand) + 1, sizeof(char)); 
	while (exp.token && exp.token[exp.index])
	{
		if (ft_handle_replace_exp(expand, table, &exp, isexpand))
			continue;
		expand[exp.size] = exp.token[exp.size];
		++exp.size;
		++exp.index;
	}
	return (expand);
}

void ft_remove_empty_args(t_command *command)
{
	char	*tmp;
	size_t	i;
	
	tmp = NULL;
	i = 0;
	while (command->argument && command->argument->arguments && command->argument->arguments[i])
	{
		if (!ft_strlen(command->argument->arguments[i]))
		{
			tmp = command->argument->arguments[i];
			command->argument->arguments[i] = command->argument->arguments[i + 1];
			free(tmp);
		}
		++i;
	}
}

void ft_expand_env(t_command *command, t_symbol_table *table)
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
		ft_remove_empty_args(command);
	}
}