#include "shell.h"

//avelacnel structurayum PWD-in u OLDPWD-in poxelu pahy))) 

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
}

// int  main(int argc, char **argv, char **env)
// {
// 	cd(argc, argv, env);
//     return (0);
// }