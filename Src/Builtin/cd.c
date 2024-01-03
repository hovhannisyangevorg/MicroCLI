#include "shell.h"

    
// int cd(int argc, char **argv, char **env)
// {
//     (void)argc;
    
// }

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