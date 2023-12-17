# include "shell.h"

t_env *env_init(char **env, t_env *my_env)
{
    int i;

    i = 0;
    while (env[i])
    {
        my_env = lst_push_back(&my_env, new_list(env[i]));
        i++;
        if (env[i] == NULL)
            my_env = lst_push_back(&my_env, new_list("$?=0"));   
    }
    return (my_env);
}

// int main(int argc, char **argv, char **env)
// {
//     (void)argc;
//     (void)argv;
//     t_env *my_env = NULL;

//     env_init(env, my_env);
//     printf("%s", my_env->key);
//     printf("%s", my_env->data);
//     // int i = -1;
//     // while (env[++i])
//     //     printf("%s\n", env[i]);
// }