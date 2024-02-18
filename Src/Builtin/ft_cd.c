/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:49:00 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/13 20:40:18 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_cd(t_command* command, t_symbol_table* table)
{
    (void)command;
    (void)table;
    char *cwd;
    char *oldcwd;
    char* dest;


    oldcwd = getcwd(NULL, 0);
    if (command->argument && command->argument->arguments && command->argument->arguments[0])
    {
        if (command->argument->arguments[1] && command->argument->arguments[2])
        {
            ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
            return 1;
        }
        if (!command->argument->arguments[1])
        {
            dest = ft_get_env(table->env, "HOME");
            if (!dest)
            {
                ft_putendl_fd("cd: HOME is not set", STDERR_FILENO);
                return 1;
            }
            else if (chdir(dest) < 0)
            {
                perror("cd: ");
                return 1;
            }
        }
        else if (command->argument->arguments[1][0] == '-')
        {
            if (command->argument->arguments[1][1] == '\0')
            {
                dest = ft_get_env(table->env, "OLDPWD");
                if (!dest)
                {
                    ft_putendl_fd("cd: OLDPWD is not set", STDERR_FILENO);
                    return 1;
                }
                else if (chdir(dest) < 0)
                {
                    perror("cd: ");
                    return 1;
                }

            }
            else
            {
                ft_putstr_fd("cd: ", STDERR_FILENO);
                ft_putstr_fd(command->argument->arguments[1], STDERR_FILENO);
                ft_putendl_fd(": invalid option", STDERR_FILENO);
                return 1;
            }
        }
        else if (chdir(command->argument->arguments[1]) < 0)
        {
            ft_putstr_fd("cd: ", STDERR_FILENO);
            ft_putstr_fd(command->argument->arguments[1], STDERR_FILENO);
            ft_putstr_fd(": ", STDERR_FILENO);
            ft_putendl_fd(strerror(errno), STDERR_FILENO);
            return 1;
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
