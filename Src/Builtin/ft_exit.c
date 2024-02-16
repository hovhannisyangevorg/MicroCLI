/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:49:33 by gevorg            #+#    #+#             */
/*   Updated: 2024/02/13 20:41:45 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int is_numeric(char *str)
{
    size_t i;

    i = 0;
    while(str && str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        ++i;
    }
    return (1);
}

long long ft_atoll(char* str)
{
	size_t	        i;
	long long		sign;
	long long		res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	return (sign * res);

}

//TODO handle arguments and non-numerics
int	ft_exit(t_command *command, t_symbol_table* table)
{
    unsigned long long   status;
    size_t               i;
    size_t               ac;
    printf("exit\n");
    (void)command;
    (void)table;
    
    if (command->argument && command->argument->arguments && command->argument->arguments[0] && command->argument->arguments[1])
    {
        i = 1;
        ac = 0;
        while (command->argument->arguments[i])
        {
            if (!is_numeric(command->argument->arguments[i]))
            {
                ft_panic_shell("exit: ", "numeric argument required");
                exit(2);
            }
            ++i;
            ++ac;
        }
        status = ft_atoll(command->argument->arguments[1]);
        if (status > LLONG_MAX)
        {
            ft_panic_shell("exit: ", "numeric argument required");
            exit(2);
        }
        else if (ac > 1)
            ft_panic_shell("exit: ", "too many arguments");
        else
            exit (i % 255);
        return (2);
    }
    exit (EXIT_SUCCESS);
}


