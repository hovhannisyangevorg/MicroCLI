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
