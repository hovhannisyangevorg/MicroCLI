/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types_method.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:05:00 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 21:54:34 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_is_redirection(t_token_type type)
{
	return (type == READ || type == WRITE || type == HEREDOC || type == APPEND);
}

int	ft_is_breckets(t_token_type type)
{
	return (type == OPBREK || type == CLBREK);
}

int	ft_is_special_node(t_token_type type)
{
	return (type == ROOT || type == SUBSHELL || \
			type == ARGUMENT || type == REDIRECT);
}

int	ft_isoperator(t_token_type type)
{
	return (type == PIPE || type == AND || \
			type == OR || type == SEMI);
}

int	ft_iscommand(t_token_type type)
{
	return (type == TEXT || ft_is_redirection(type) || ft_is_breckets(type));
}
