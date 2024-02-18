/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_method.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:02:45 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/18 16:43:31 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list_token *ft_init_list()
{
	t_list_token *list;

	list = (t_list_token *)malloc(sizeof(t_list_token));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

void	ft_init_token(t_token *node, int type, char *elem)
{
	node->quate_type = 0;
	node->type = type;
	node->token = elem;
	node->next = NULL;
	node->prev = NULL;
}

void	ft_push_back(t_list_token *list, int type, const char *token)
{
	t_token	*new;
	t_token	*tmp;

	if (!list)
		return ;
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return ;
	ft_init_token(new, type, ft_strdup(token));
	if (list->head == NULL)
	{
		list->head = new;
		list->tail = new;
	}
	else
	{
		tmp = list->head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		list->tail = new;
	}
	++list->size;
}

void	ft_push_front(t_list_token *list, int type, const char *token)
{
	t_token	*new;

	if (!list)
		return ;
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return ;
	ft_init_token(new, type, ft_strdup(token));
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
		++list->size;
		return;
	}
	new->next = list->head;
	list->head->prev = new;
	list->head = new;
	++list->size;
}

void	ft_pop_front(t_list_token *list)
{
	t_token	*tmp;

	if (list == NULL || list->head == NULL)
		return ;
	if (list->size == 1)
		list->tail = NULL;
	tmp = list->head;
	list->head = (list->head)->next;
	if (list->head)
		list->head->prev = NULL;
	free(tmp->token);
	free(tmp);
	--list->size;
}

void	ft_pop_back(t_list_token *list)
{
	t_token	*tmp;
	t_token	*prev;

	if (list == NULL || list->head == NULL)
		return ;
	tmp = list->head;
	prev = NULL;
	while (tmp && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == NULL)
	{
		free(tmp->token);
		free(tmp);
		list->head = NULL;
	}
	else
	{
		prev->next = NULL;
		free(tmp->token);
		free(tmp);
	}
	list->tail = prev;
	--list->size;
}

void	ft_free_list(t_list_token *list)
{
	t_token	*tmp;
	t_token	*next;

	if (list == NULL)
		return ;
	if (list->head == NULL)
	{
		free(list);
		return;
	}
	tmp = list->head;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->token);
		free(tmp);
		tmp = next;
	}
	list->head = NULL;
	list->size = 0;
	free(list);
}

void	ft_print_list(t_token* list)
{
	t_token* current;

	current = list;
	while (current)
	{
		printf("Type: %u, Token: %s\n", current->type, current->token);
		current = current->next;
    }
}
