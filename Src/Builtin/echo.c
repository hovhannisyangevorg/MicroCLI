#include "shell.h"

// #include "builtins.h"

static int check_flag(char *arg);

size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (ptr && *ptr)
		ptr++;
	return (ptr - str);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}


//

int echo(int argc, char **argv,char **env)
{
    (void)env;

    int i;
    int flag;

    if (!argv[1])
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        return (1);
    }
    i = 2;
    while (i < argc)
    {
        flag = check_flag(argv[i]);
        ft_putstr_fd(argv[i], STDOUT_FILENO);
        ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if (flag == 1)
      ft_putstr_fd("\n", STDOUT_FILENO);
    return (1);
}


static int check_flag(char *arg)
{
    int i;

    i = 0;
    if (arg[i] == '-')
        i++;
    while (arg[i] && arg[i] == 'n')
        i++;
    if (arg[i] == '\0')
        return (1);
    return (0);
}

// int main(int argc, char **argv, char **env)
// {
//     echo(argc, argv,env);
// }