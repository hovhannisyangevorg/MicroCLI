/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armhakob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
<<<<<<< HEAD:Src/Shell/main.c
/*   Updated: 2023/10/23 20:24:34 by armhakob         ###   ########.fr       */
=======
/*   Updated: 2023/09/26 15:09:58 by armhakob         ###   ########.fr       */
>>>>>>> d87676c0f4a9627384897b952b54dc3ef0b83cdc:src/main.c
/*                                                                            */
/* ************************************************************************** */

/**
 * Victory belongs to anyone who perseveres on any path.
 */

<<<<<<< HEAD:Src/Shell/main.c
#include "shell.h"
=======
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

#define SEPARARTORS "|<>|&()"

typedef enum flags
{
	// PIPE 		= 0x000001,
	// HEREDOC 	= 0x000010,
	// REDIRECT 	= 0x010000,
	// APPEND		= 0x000100,
	QUOTE		= 0x100000,
	DQUOTE		= 0x001000
} flags_t;

struct token_s
{
	int flags;
	char* token;
	struct token_s* next; 
};


// char* split(char* str, char* delims)
// {

// }


int flags = 0;

// 1 validation balanced
//  quotes, brackets -> (), "", ''

// validation of separators synax errors

int checkBrackets(char* str);
int checkQuotes(char* str, char c);

>>>>>>> d87676c0f4a9627384897b952b54dc3ef0b83cdc:src/main.c

int main()
{
<<<<<<< HEAD:Src/Shell/main.c
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
=======
	printf(HEADER"\n");
	flags |= QUOTE;
	// flags |= REDIRECT;

	if ((flags & QUOTE) == QUOTE)
	{
		printf("PIPE exists\n");
	}
	// else
	// {
	// 	printf("p not exist\n");
	// }
	// if ((flags & REDIRECT) == REDIRECT)
	// {
	// 	printf("Redirect exists\n");
	// }
	// else
	// {
	// 	printf("r not exist\n");
	// }
	// if ((flags & HEREDOC) == HEREDOC)
	// {
	// 	printf("HERedoc exists\n");
	// }
	// else
	// {
	// 	printf("h not exist\n");
	// }
	while (1)
	{
		write(1, "$> ", ft_strlen("$> "));
		char* line = 0;
		
		if (ft_getline(0, &line) <= 0)
			break;
	}
	
	return (0);
>>>>>>> d87676c0f4a9627384897b952b54dc3ef0b83cdc:src/main.c
}
