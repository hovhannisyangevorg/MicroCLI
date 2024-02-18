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
#include <stdint.h>

int is_numeric(char *str)
{
    size_t i;

    i = 0;
    if (str && str[i] && (str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
        return (1);
    while(str && str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        ++i;
    }
    return (1);
}


int ft_ismultiply_overflow_u(long a, long b)
{
    if (a == 0 || b == 0)
        return 0;
    
    if (a > LONG_MAX / b || a < LONG_MIN / b)
        return 1;
    return 0;
}

int ft_isadd_overflow_u(long a, long b)
{
    if (a > 0 && b > 0 && a > LONG_MAX - b)
        return 1;
    if (a < 0 && b < 0 && a < LONG_MIN - b)
        return 1;
    return 0;
}



int ft_ismultiply_overflow_size_t(size_t a, size_t b) {
    size_t result;

    if (a == 0 || b == 0)
        return 0;
    result = a * b;
    if (result / a != b)
        return 1;
    return 0;
}

int ft_isadd_overflow_size_t(size_t a, size_t b)
{
    size_t result;

    result = a + b;
    if (result < a || result < b)
        return 1;
    return 0;
}



long long ft_atoll(char* str, int* is_overflowed)
{
	size_t	        i;
	long		    sign;
	size_t		    res;

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
        if (ft_ismultiply_overflow_u(res, 10))
            *is_overflowed = 1;
        size_t tmp = res * 10;
         if (ft_isadd_overflow_u(tmp, str[i] - '0'))
             *is_overflowed = 1;
		res = tmp + (str[i] - '0');
		++i;
	}
	return (sign * res);

}

//TODO handle arguments and non-numerics
int	ft_exit(t_command *command, t_symbol_table* table)
{
    size_t              status;
    size_t               i;
    int                  is_overflow;
    size_t               ac;
    unsigned char        st;
    printf("exit\n");
    is_overflow = 0;
    (void)command;
    (void)table;
    
    if (command->argument && command->argument->arguments && command->argument->arguments[0] && command->argument->arguments[1])
    {
        i = 1;
        ac = 0;
        while (command->argument->arguments[i])
        {
            if (ac >= 1)
            {
                ft_panic_shell("exit: ", "too many arguments");
                return (EXIT_FAILURE);
            }
            ++i;
            ++ac;
        }
        i = 1;
        while (command->argument->arguments[i])
        {
            if (!is_numeric(command->argument->arguments[i]))
            {
                ft_panic_shell("exit: ", "numeric argument required");
                exit(2);
            }
            ++i;
        }
        status = ft_atoll(command->argument->arguments[1], &is_overflow);
        if (is_overflow)
        {
            ft_panic_shell("exit: ", "numeric argument required");
            exit(EXIT_FAILURE);
        }
        else
        {
            st = status;
            exit (st);
        }
    }
    exit (EXIT_SUCCESS);
}


