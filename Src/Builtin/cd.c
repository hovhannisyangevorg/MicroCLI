#include "shell.h"

//avelacnel structurayum PWD-in u OLDPWD-in poxelu pahy))) 
/*
int cd(int argc, char **argv, char **env)
{
    char *pwd;
    char *old_pwd;
	char *path;

    (void)argc;
    (void)env;

    path = NULL;
    old_pwd = NULL;
    pwd = getenv("PWD");
    if (!argv[1])
    {
        path = getenv("HOME");
        old_pwd = pwd;
        pwd = path;
    }
	else
	{
		path = argv[1];
		old_pwd = pwd;
		pwd = path;
	}

	if (chdir(path) == 0) {
        printf("Current working directory changed to: %s\n", path);
    } else {
        perror("chdir");
        return 1; 
    }

    return (0);
}*/

int cd (char **argv, t_env **my_env)
{
    char *pwd;
    char *old_pwd;
    t_env *tmp;

    old_pwd = NULL;
    pwd = getenv("PWD");
    tmp = *my_env;
    if (!argv[1])
    {
        old_pwd = pwd;
        pwd = getenv("HOME");
    }
    else
    {
        old_pwd = pwd;
        pwd = argv[1];
    }

    if (!ft_strcmp(tmp->key, "PWD")){
        tmp->data = pwd;
        printf("key %s\n", tmp->key);
    }
    if (!ft_strcmp(tmp->key, "OLdPWD"))
        tmp->data = old_pwd;

    if (chdir(pwd) == 0)
    {
        printf("Current working directory change to : %s\n", pwd);
    } else {
        perror("chdir");
        return (1);
    }

    return (0);
}
