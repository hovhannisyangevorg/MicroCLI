#include "shell.h"


int ft_is_redirection(t_token_type type)
{
	return (type == READ || type == WRITE || type == HEREDOC || type == APPEND);
}

int ft_is_brace(t_token_type type)
{
	return (type == OPBREK || type == CLBREK);
}

int ft_is_special_node(t_token_type type)
{
    return (type == ROOT || type == SUBSHELL || type == ARGUMENT || type == REDIRECT);
}

int ft_isoperator(t_token_type type)
{
	return (type != TEXT && !ft_is_redirection(type) && !ft_is_brace(type));
}

char* ft_get_type(t_token_type type)
{
    if (type == OR)
        return ft_strdup("||");
    else if (type == AND)
        return ft_strdup("&&");
    else if (type == JOB)
        return ft_strdup("&");
    else if (type == READ)
        return ft_strdup("<");
    else if (type == APPEND)
        return ft_strdup(">>");
    else if (type == WRITE)
        return ft_strdup(">");
    else if (type == HEREDOC)
        return ft_strdup("<<");
    else if (type == SEMI)
        return ft_strdup(";");
    else if (type == SEMITWO)
        return ft_strdup(";;");
    else if (type == PIPE)
        return ft_strdup("|");
    else if (type == OPBREK)
        return ft_strdup("(");
    else if (type == CLBREK)
        return ft_strdup(")");
    else if (type == SUBSHELL)
        return ft_strdup("SubShell");
    else
        return ft_strdup("Unknown");
    
}

t_token_type ft_get_type_map(int type)
{
    if (type == MOR)
        return OR;
    else if (type == MAND)
        return AND;
    else if (type == MJOB)
        return JOB;
    else if (type == MREAD)
        return READ;
    else if (type == MAPPEND)
        return APPEND;
    else if (type == MWRITE)
        return WRITE;
    else if (type == MHEREDOC)
        return HEREDOC;
    else if (type == MSEMI)
        return SEMI;
    else if (type == MSEMITWO)
        return SEMITWO;
    else if (type == MPIPE)
        return PIPE;
    else if (type == MOPBREK)
        return OPBREK;
    else if (type == MCLBREK)
        return CLBREK;
    else if (type == MTEXT)
        return TEXT;
    else
        return NNULL;
}
