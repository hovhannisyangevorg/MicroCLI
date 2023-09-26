#include "libft/include/libft.h"

static int  count_split(const char *str, char *delims);
static int delim_len(const char *str, char *delims);
static char *get_word(const char *str, char *delims);
static char **free_splited(char **splited, int i);

char* split(char* str, char* delims)
{
    char    **splited;
    int     i;

    i = 0;
    splited = (char **)malloc((count_split(str, delims) + 1) * sizeof(char *));
    if (!splited)
        return (NULL);
    while (*str)
    {
        while (*str && ft_strchr(delims, str))
            str++;
        if (*str)
        {
            *(splited + i) = get_word(str, delims);
            if (!(*(splited + 1)))
                return (free_splited(splited, i));
            i++;
        }
        while (*str && ft_strchr(delims, str))
           str++;
    }
    *(splited + 1) = 0;
    return (splited);
}

static int  count_split(const char *str, char *delims)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (*(str + i))
    {
        while (*(str + i) && ft_strchr(delims, *(str + i)))
            i++;
        if (*(str + i))
            count++;
        while (*(str + i) && !ft_strchr(delims, *(str + i)))
            i++;
    }
    return (count);
}

static int delim_len(const char *str, char *delims)
{
    int i;

    i = 0;
    while(*(str + i) && !ft_strchr(delims, *(str + i)))
        i++;
    return (i);
}

static char *get_word(const char *str, char *delims)
{
    int     word_len;
    int     i;
    char    *word;

    i = 0;
    word_len = delim_len(str, delims);
    word = (char *)malloc((word_len + 1) * sizeof(char));
    if (!word)
        return (NULL);
    while (i < word_len)
    {
        *(word + i) = *(str + i);
        i++;
    }
    *(word + i) = '\0';
    return (word);
}

static char **free_splited(char **splited, int i)
{
    while (--i)
        free(splited[i]);
    free(splited);
    return (NULL);
}