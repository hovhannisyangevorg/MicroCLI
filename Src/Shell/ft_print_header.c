/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehovhan <gehovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:41:59 by gehovhan          #+#    #+#             */
/*   Updated: 2024/02/27 18:17:12 by gehovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_print_header(void)
{
	printf("\033[0;32m%s%s%s%s%s%s\033[0m", \
		"███╗   ███╗██╗███╗   ██╗██╗\
███████╗██╗  ██╗███████╗██╗     ██╗     \n", \
		"████╗ ████║██║████╗  ██║██║\
██╔════╝██║  ██║██╔════╝██║     ██║     \n", \
		"██╔████╔██║██║██╔██╗ ██║██║\
███████╗███████║█████╗  ██║     ██║     \n", \
		"██║╚██╔╝██║██║██║╚██╗██║██║\
╚════██║██╔══██║██╔══╝  ██║     ██║     \n", \
		"██║ ╚═╝ ██║██║██║ ╚████║██║\
███████║██║  ██║███████╗███████╗███████╗\n", \
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝\
╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}
