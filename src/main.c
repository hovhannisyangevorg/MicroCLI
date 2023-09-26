/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armhakob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2023/09/26 15:09:58 by armhakob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Victory belongs to anyone who perseveres on any path.
 */

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


int	main()
{
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
}
