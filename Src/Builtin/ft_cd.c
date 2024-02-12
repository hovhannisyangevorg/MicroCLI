#include "shell.h"
#include <limits.h>
    
int ft_cd(t_command* command, t_symbol_table* table)
{
    (void)command;
    (void)table;
    char *cwd;
    char *oldcwd;


    oldcwd = getcwd(NULL, 0);
    if (command->argument && command->argument->arguments && command->argument->arguments[0])
    {
        if (!command->argument->arguments[1])
        {
            char* home = ft_get_env(table->env, "HOME");
            if (!home)
            {
                ft_putendl_fd("cd: HOME is not set", STDERR_FILENO);
                return 1;
            }
            else if (chdir(home) < 0)
            {
                perror("cd: ");
                return errno;
            }
        }
        else if (chdir(command->argument->arguments[1]) < 0)
        {
            perror("cd: ");
            return errno;
        }


    }
    cwd = getcwd(NULL, 0); 
    if (!cwd)
    {
        perror("cd: ");
        return errno;
    }
    ft_set_env(table->env, (t_hash_data){"OLDPWD", oldcwd, NORMAL});
    ft_set_env(table->env, (t_hash_data){"PWD", cwd, NORMAL});
    return 0;

    
}

// int  main(int argc, char **argv, char **envp)
// {
//     char *pwd;
//     char *home;
//     char *old_pwd;

//     (void)argc;
//     (void)envp;
//     pwd = getenv("PWD");
//     if (!argv[0])
//     {
//         home = getenv("HOME");
//         old_pwd = pwd;
//         pwd = home;
//     }
//     chdir(home);
//     printf("%s\n", pwd);
//     return (0);
// }