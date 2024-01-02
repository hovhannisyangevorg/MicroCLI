#include "shell.h"


int ft_ignore_quots(char *str, char quot, size_t i)
{
	if (str && str[i])
	{
		++i;
		while (str[i] && str[i] != quot)
			++i;
	}
	return (i);
}

char *ft_tokenize_with_space(char *str, int* type)
{
    static char *next_token;
    if (str) {
        next_token = str;
    }
    if (!next_token) {
        return NULL;
    }
    char *token_start = next_token;
	int i = 0;
    *type = NNULL;
	if (token_start[i] == '\"' || token_start[i] == '\'')
	{
        *type = MTEXT;
		i = ft_ignore_quots(token_start, token_start[i], 0);
	}
    while(token_start[i])
    {
        if (ft_isspace(token_start[i])) {
            *type = MTEXT;
            token_start[i] = '\0';
            ++i;
            while (token_start[i] && ft_isspace(token_start[i]))
                ++i;
            if (!token_start[i])
                next_token = NULL;
            else
                next_token = token_start + i;
            return token_start;
        }
        ++i;

    }
    next_token = NULL;
    return token_start;
}


char *ft_tokenize_with_delims(char *str,  char *delim, int* type)
{
    static char *next_token;

    if (str) {
        next_token = str;
    }
    if (!next_token) {
        return NULL;
    }
    char *token_start = next_token;
	int i = 0;
    int is_one_sym = 0;
    *type = MNNULL;
	if (token_start[i] == '\"' || token_start[i] == '\'')
	{
        *type = MTEXT;
		i = ft_ignore_quots(token_start, token_start[i], 0);
	}
    while(token_start[i])
    {
        if (ft_strchr(delim, token_start[i])) {
           if (token_start[i] && token_start[i + 1] && token_start[i] == token_start[i + 1] 
                && !ft_is_brace(ft_get_type_map(token_start[i])))
           {
                is_one_sym = 0;
                *type = -token_start[i];
           }
            else
            {
                is_one_sym = 1;
                *type = token_start[i];
            }
            token_start[i] = '\0';
            if (!is_one_sym)
                ++i;
            next_token = token_start + i + 1;
            return token_start;
        }
        else
            *type = MTEXT;
        ++i;

    }
    next_token = NULL;
    return token_start;
}

t_list_token* ft_tokenize_string_space(char *input)
{
    t_list_token* list;
    char *token;
    int type;

    type = 0;
    list = (t_list_token *)malloc(sizeof(t_list_token));
	ft_init_list(list);
    token = ft_tokenize_with_space(input, &type);

    while (token != NULL)
    {
        ft_push_back(list, type, ft_strdup(token));
        token = ft_tokenize_with_space(NULL, &type);
    }
    return list;
}


t_list_token* ft_tokenize(char *input, char* delims)
{
    t_list_token* list;
    t_list_token* list2;
    char *token;
    int type;

    type = 0;
    list = (t_list_token *)malloc(sizeof(t_list_token));
	ft_init_list(list);
    list2 = ft_tokenize_string_space(input);
    t_token* head = list2->head;
    while(head)
    {
        token = ft_tokenize_with_delims(head->token, delims, &type);
        while (token != NULL) {
            if (type != MTEXT && type)
            {
                if (*token)
                    ft_push_back(list, TEXT, ft_strdup(token));
                ft_push_back(list, ft_get_type_map(type), ft_get_type(ft_get_type_map(type)));
            }
            else if (type)
                ft_push_back(list, ft_get_type_map(type), ft_strdup(token));
            token = ft_tokenize_with_delims(NULL, delims, &type);
        }
        head = head->next;
    }
    return list;
}