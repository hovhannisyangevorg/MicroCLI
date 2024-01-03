#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h" 

typedef struct s_env
{
    struct s_env    *next;
    struct s_env    *prev;
    char    *pwd;
    char    *data;
    char    *key;
    int hushir_indz;
}   t_env;

t_env *lst_push_back(t_env **list, t_env *new);
t_env *new_list(char *env);

t_env *env_init(char **env, t_env *my_env);
void write_env(t_env **env);
t_env *init_pwd(t_env *my_env);
void	pwd_helper(t_env *my_env);
int	unset_helper(char **argv, t_env *my_env);
int check_unset(char *argv);

int echo(int argc, char **argv, char **env);
int env_m(int argc, char **argv, char **env);
int pwd(int argc, char **argv, char **env);
int cd(int argc, char **argv, char **env);
int	unset(int argc, char **argv, char **env);



#endif