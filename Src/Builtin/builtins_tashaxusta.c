#include "shell.h"

t_env *lst_push_back(t_env **list, t_env *new)
{
    t_env *tmp;

    tmp = *list;
    if (tmp == NULL)
        list = &new;
    else
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
        new->prev = tmp;
    }
    return (*list);
}

t_env *new_list(char *env)
{
    int i;
    t_env *tmp;

    i = 0;
    
    tmp = (t_env *)malloc(sizeof(t_env));
    tmp->next = NULL;
    tmp->prev = NULL;
    while (env && env[i] != '\0' && env[i] != '=')
        i++;
    tmp->key = ft_substr(env, 0, (size_t)i - 1);
    tmp->data = ft_substr(env, i + 1, ft_strlen(&env[i + 1]));
    tmp->pwd =  NULL;
    if (!ft_strcmp(tmp->key, "PWD"))
        tmp->pwd = ft_strdup(tmp->data);
    tmp->hushir_indz = 0;
    if (!ft_strcmp(tmp->key, "$?"))
        tmp->hushir_indz = 2;
    return (tmp);
}