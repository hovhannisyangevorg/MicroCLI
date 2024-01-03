#include "shell.h"

char* ft_get_error_message(t_status_codes code)
{
    if (code == SUCCESS_CODE)
        return NULL;
    if (code == UNEXPECTED_PIPE)
        return ft_strdup("Missing token near \'|\'");
    if (code == UNEXPECTED_REDIRECT)
        return ft_strdup("Missing token near redirection");
    if (code == EMPTY_SUBSHELL)
        return ft_strdup("Missing token near \'(\' or \')\'");
    if (code == MISSING_OPERATOR)
        return ft_strdup("Missing operator near token");
    if (code == MISSING_TOKEN)
        return ft_strdup("Missing token near operator");
    return ft_strdup("Unknown error");
}