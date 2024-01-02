#include "shell.h"


t_list_token* ft_sublist(t_token* start, t_token* end)
{
	t_list_token* lst;

	lst = malloc(sizeof(t_list_token));
	ft_init_list(lst);
	while (start != end)
	{
		ft_push_back(lst, start->type, start->token);
		start = start->next;
	}
	return lst;
}

t_token* ft_find_list(t_token_type type, t_token* start)
{
	t_token* token;

	token = start;
	while (token)
	{
		if (token->type == type)
			return token;
		token = token->next;
	}
	return NULL;
}


t_token*	ft_find_close_list(t_token* open)
{
	if (!open)
		return (NULL);
	int count;
	t_token* node;

	node = open->next;
	count = 1;
	while (node)
	{
		if (node->type == OPBREK)
			++count;
		else if (node->type == CLBREK)
		{
			--count;
			if (0 == count)
				return (node);
		}
		node = node->next;
	}
	return (NULL);
}