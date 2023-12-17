#include "shell.h"

// t_env *init_pwd(t_env *my_env)
// {
// 	t_env *tmp;

// 	tmp = my_env;
// 	while (tmp->next != NULL)
// 	{
// 		if (ft_strcmp(tmp->key,"PWD") == 0)	
// 	}
// } 

void	pwd_helper(t_env *my_env)
{
	char *pwd;
	t_env *tmp;
	
	tmp = my_env;
	pwd = getcwd(NULL,0);
	if (pwd != NULL)
		printf("%s\n", pwd);
	else if (!ft_strcmp(tmp->key, "PWD"))
	{
		printf("%s", tmp->pwd);
		free(tmp->data);
		tmp->data = tmp->pwd;
	}
	free(pwd);
}

int pwd(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_env *my_env;

	my_env = NULL;
	my_env = env_init(env, my_env);

	pwd_helper(my_env);
	return (1);
}

// int main(int argc, char **argv, char **env)
// {
// 	printf ("%d", pwd(argc, argv, env));
// }