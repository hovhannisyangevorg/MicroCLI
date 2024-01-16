/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:37:04 by gevorg            #+#    #+#             */
/*   Updated: 2024/01/13 14:35:24 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() 
// {
// 	int a = 15;
//     pid_t pid = fork();

// 	a++;
// 	if (pid < 0) {
//         fprintf(stderr, "fork failed\n");
//         return (1);
//     }
// 	else if (pid == 0)
// 	{
//         printf("I am the child process (PID: %d)\n", a);
//     } else 
// 	{
// 		a++;
//         printf("I am the parent process (PID: %d).\n", a);
// 	}
//     return (0);
// }