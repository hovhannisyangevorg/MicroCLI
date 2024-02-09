/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:05:13 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/20 18:05:16 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


void	sig_handler_c(int signum)
{
    if (signum == SIGINT)
    {
        // printf("\n");
        // rl_on_new_line();
        // rl_replace_line("", 0);
        // rl_redisplay();
    }
}

// Function to acquire a lock on a file descriptor
void lock_file(int fd, short type)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock entire file
    fcntl(fd, F_SETLKW, &lock);
}

// Function to release a lock on a file descriptor
void unlock_file(int fd)
{
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Unlock entire file
    fcntl(fd, F_SETLKW, &lock);
}

char    *ft_get_line()
{
    char	*line;

    // sleep(1);
    line = readline("Minishell $> ");
    if (line)
        add_history(line);
    return (line);
}
