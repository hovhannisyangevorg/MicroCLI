#include "shell.h"

void export_parsing(char **argv)
{
    int i;

    i = 1;
    while (argv[i])
    {
        if (argv[i][0] != '_' || (!(argv[i][0] >= 'a' 
            && argv[i][0] <= 'z') || !(argv[i][0] >= 'A' && argv[i][0] <= 'Z')))
            {
                printf("Minishell: export: `%s`: not a valid identifier\n", argv[i]);
                exit(1);
            }
        i++;
    }
}

void export_helper(t_env *my_env)
{
	t_env *tmp;
	int hushir_indz;

	tmp = my_env;
	hushir_indz = 0;
	while (tmp != NULL)
	{
		if (tmp->hushir_indz == 0)
			printf("declare -x %s=%s\n", tmp->key, tmp->data);
		if (tmp->hushir_indz == 2)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	tmp = my_env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			hushir_indz = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (hushir_indz == 0)
		printf("declare -x OLDPWD\n");
}

void export_helper_args(char **argv, t_env *my_env)
{
	int i;

    i = 1;
    while (argv[i])
    {
        my_env = lst_push_back(&my_env, new_list(argv[i]));
        i++;  
    }
}

int export(int argc, char **argv, char **env)
{
	(void)argv;
	t_env *my_env;

	my_env = NULL;
	my_env = env_init(env, my_env);
    export_parsing(argv);
	if (argc < 2)
		export_helper(my_env);
	else
	{
		export_helper_args(argv, my_env);
		while (my_env != NULL)
		{
			printf ("%s=%s\n",my_env->key, my_env->data);
			my_env = my_env->next;
		}
	}
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
// 	printf("%i", export(argc, argv, env));
// }