#include "shell.h"


int	ft_export(t_command* command, t_hash_table* env)
{
	(void)command;
	t_hash_table_arr arr = ft_sort_env(env);
	print_env_table(arr);
	free(arr.table);
	// (void)command;
	// (void)env;
	return(0);
}

// void export_helper(t_env *my_env)
// {
// 	t_env *tmp;
// 	int hushir_indz;

// 	tmp = my_env;
// 	hushir_indz = 0;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->hushir_indz == 0)
// 			printf("declare -x %s=%s\n", tmp->key, tmp->data);
// 		if (tmp->hushir_indz == 2)
// 			printf("declare -x %s\n", tmp->key);
// 		tmp = tmp->next;
// 	}
// 	tmp = my_env;
// 	while (tmp != NULL)
// 	{
// 		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
// 		{
// 			hushir_indz = 1;
// 			break;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (hushir_indz == 0)
// 		printf("declare -x OLDPWD\n");
// }

// void export_helper_args(char **argv, t_env *my_env)
// {
// 	int i;

//     i = 1;
//     while (argv[i])
//     {
//         my_env = lst_push_back(&my_env, new_list(argv[i]));
//         i++;  
//     }
// }

// int export(int argc, char **argv, char **env)
// {
// 	(void)argv;
// 	t_env *my_env;

// 	my_env = NULL;
// 	my_env = env_init(env, my_env);

// 	if (argc < 2)
// 		export_helper(my_env);
// 	else
// 	{
// 		export_helper_args(argv, my_env);
// 		while (my_env != NULL)
// 		{
// 			printf ("%s=%s\n",my_env->key, my_env->data);
// 			my_env = my_env->next;
// 		}
// 	}
// 	return (0);
// }

// int main(int argc, char **argv, char **env)
// {
// 	printf("%i", export(argc, argv, env));
// }