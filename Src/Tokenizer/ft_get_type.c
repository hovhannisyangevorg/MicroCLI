/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:54:37 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 21:56:58 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_get_type(t_token_type type)
{
	if (type == OR)
		return (ft_strdup("||"));
	else if (type == AND)
		return (ft_strdup("&&"));
	else if (type == JOB)
		return (ft_strdup("&"));
	else if (type == READ)
		return (ft_strdup("<"));
	else if (type == APPEND)
		return (ft_strdup(">>"));
	else if (type == WRITE)
		return (ft_strdup(">"));
	else if (type == HEREDOC)
		return (ft_strdup("<<"));
	else if (type == SEMI)
		return (ft_strdup(";"));
	else if (type == SEMITWO)
		return (ft_strdup(";;"));
	else if (type == PIPE)
		return (ft_strdup("|"));
	else if (type == OPBREK)
		return (ft_strdup("("));
	else if (type == CLBREK)
		return (ft_strdup(")"));
	else if (type == SUBSHELL)
		return (ft_strdup("SubShell"));
	else if (type == COMMAND)
		return (ft_strdup("Command"));
	else
		return (ft_strdup("Unknown"));
}

t_token_type	ft_get_type_map(int type)
{
	if (type == MOR)
		return (OR);
	else if (type == MAND)
		return (AND);
	else if (type == MJOB)
		return (JOB);
	else if (type == MREAD)
		return (READ);
	else if (type == MAPPEND)
		return (APPEND);
	else if (type == MWRITE)
		return (WRITE);
	else if (type == MHEREDOC)
		return (HEREDOC);
	else if (type == MSEMI)
		return (SEMI);
	else if (type == MSEMITWO)
		return (SEMITWO);
	else if (type == MPIPE)
		return (PIPE);
	else if (type == MOPBREK)
		return (OPBREK);
	else if (type == MCLBREK)
		return (CLBREK);
	else if (type == MTEXT)
		return (TEXT);
	else
		return (NNULL);
}
