/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armhakob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/10/23 20:24:34 by armhakob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Victory belongs to anyone who perseveres on any path.
 */

#include "shell.h"

int main()
{
	char *line;
	t_token *head;

	signal(SIGINT, sig_handler_c);
	// rl_catch_signals = 0;
	while (1)
	{
		line = ft_get_line();
		ft_is_balanc(line);
		if (!line)
			return (0);
		head = ft_multi_split(line, SEPARARTORS);

		
		ft_print_list(head);
		ft_free_list(&head);
		free(line);
    }
    clear_history();
    return (0);
}
