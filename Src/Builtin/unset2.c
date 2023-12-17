#include "shell.h"

//ashxatox
	
int	unset_helper(char **argv, t_env *my_env)
{

	int i;
	t_env *tmp;

	i = 0;
	tmp = my_env;
	while (argv && argv[i++])
	{
		while (tmp != NULL)
		{
			if (ft_strcmp(argv[i], tmp->key) == 0)
			{
				tmp->hushir_indz = 1;
				break; 
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	unset(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_env *my_env;

	my_env = NULL;
	my_env = env_init(env, my_env);
	if (unset_helper(argv, my_env) == 0)
		return (1);
	return(0);
}

int main(int argc, char **argv, char **env)
{
	printf("%i", unset(argc, argv, env));
	// printf("%i",env_m(argc, argv, env));
	// printf ("%d", pwd(argc, argv, env));
}