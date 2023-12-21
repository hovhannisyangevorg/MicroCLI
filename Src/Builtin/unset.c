#include "shell.h"

int	unset_helper(char **argv, t_env *my_env)
{

	int i;
	t_env *tmp;

	i = 0;
	tmp = my_env;
	while (argv && argv[i++])
	{
		// if (check_unset(argv[i]) == 0)
		// 	return (1);
		while (tmp != NULL)
		{
			if (ft_strcmp(argv[i], my_env->key))
			{
				// my_env->hushir_indz = 1;
				free(my_env);
				// printf ("%s", "gttela");
				break; 
			}
			// printf ("%s=%s\n", tmp->key, tmp->data);
			tmp = tmp->next;
		}
	}
	// write_env(&my_env);	
	return (0);
}

// int check_unset(char *argv)
// {
// 	int i;

// 	i = 0;
// 	while (argv && argv[i++])
// 	{
// 		if (argv[0] != '=' && argv[i] == '=')
// 			break ;
// 		if (ft_isalpha(argv[i]) == 0 && argv[i] != '_')
// 		{
// 			perror("unset error: ");
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int	unset(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_env *my_env;

	my_env = NULL;
	my_env = env_init(env, my_env);
	if (unset_helper(argv, my_env) == 0)
	{
		// write_env(&my_env);	
		return (1);
	}
	// while (my_env != NULL)
	// 		printf("%d\n", my_env->hushir_indz);
	return(0);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_env *my_env;

// 	my_env = NULL;
// 	my_env= env_init(env, my_env);
// 	printf("%i", unset(argc, argv, env));
// 	write_env(&my_env);
// 	// printf("%i",env_m(argc, argv, env));
// 	// printf ("%d", pwd(argc, argv, env));
// }