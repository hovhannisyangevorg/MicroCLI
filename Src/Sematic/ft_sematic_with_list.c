/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sematic_with_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:39:37 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 22:06:03 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_status_codes	ft_sematic_with_list(t_command *cmd)
{
	return (ft_validate_command(ft_command_to_ast_node(cmd)));
}
