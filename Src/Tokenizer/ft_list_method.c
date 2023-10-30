/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_method.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:02:45 by gevorg            #+#    #+#             */
/*   Updated: 2023/10/30 17:23:55 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_list(t_token **head)
{
	*head = NULL;
}

void	ft_push_back(t_token **head, int type, const char *token)
{
	t_token	*new;
	t_token	*tmp;

	if (!head)
		return ;
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return ;
	new->type = type;
	new->token = ft_strdup(token);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_push_front(t_token **head, int type, const char *token)
{
	t_token	*new;

	if (!head)
		return ;
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return ;
	new->type = type;
	new->token = ft_strdup(token);
	new->next = *head;
	*head = new;
}

void	ft_pop_front(t_token **head)
{
	t_token	*tmp;

	if (!head || !(*head))
		return ;
	tmp = *head;
	*head = (*head)->next;
	free(tmp->token);
	free(tmp);
}

void	ft_pop_back(t_token **head)
{
	t_token	*tmp;
	t_token	*prev;

	if (!head || !(*head))
		return ;
	tmp = *head;
	prev = NULL;
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == NULL)
	{
		free(tmp->token);
		free(tmp);
		*head = NULL;
	}
	else
	{
		prev->next = NULL;
		free(tmp->token);
		free(tmp);
	}
}

void	ft_free_list(t_token **head)
{
	t_token	*tmp;
	t_token	*next;

	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->token);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

void	ft_print_list(t_token *head)
{
	t_token* current;

	current = head;

	while (current)
	{
		printf("Type: %d, Token: %s\n", current->type, current->token);
		current = current->next;
    }
}
