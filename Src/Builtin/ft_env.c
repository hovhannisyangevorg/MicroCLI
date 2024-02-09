#include "shell.h"

int	ft_env(t_command* command, t_hash_table* env)
{

    (void)command;
    (void)env;
	print_env(env, 0);
	return(0);
}

// void write_env(t_env **env)
// {
// 	t_env *tmp;

// 	tmp = (*env);
// 	while (tmp != NULL)
// 	{
// 		if (tmp->hushir_indz == 1)
// 			printf("%s=%s\n", tmp->key, tmp->data);
// 		tmp = tmp->next;
// 	}
// }

// int env_m(int argc, char **argv, char **env)
// {
//     (void)argc;
// 	(void)argv;

// 	t_env *my_env;

// 	my_env = NULL;
// 	my_env = env_init(env, my_env);
// 	write_env(&my_env);
	
// 	return (1);	
// }


