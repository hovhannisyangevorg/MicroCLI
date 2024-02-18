/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:40:10 by gehovhan          #+#    #+#             */
/*   Updated: 2024/02/14 22:27:13 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <signal.h>
#include <termios.h>


t_global_state g_global_state;

// #include <termio.h>

// size_t numofrec;

// void ft(t_ast_node *tree)
// {
// 	if (!tree)
// 		return ;
// 	printf("-------------------->%s\n", ft_get_type( tree->token_type));
// 	ft(tree->left);
// 	ft(tree->right);
// }


t_signal_type g_minishell_signal;

// 0924
// $OLDPWD
void print_env_args(char** env)
{
	int i = -1;
	printf("-------------args----------\n");
	while (env && env[++i])
	{
		printf("%s\n", env[i]);
	}
	printf("-------------end args----------\n");
	
}



void	ft_get_pid(t_container cont, t_hash_table *env)
{
	pid_t pid;

	(void)cont;
    pid = fork();

    if (pid < 0)
        return ;
    else if (pid == 0)
		exit(EXIT_SUCCESS);
    else
	{
		wait(NULL);
		g_global_state.pid = pid - 1;
		char* p_id = ft_itoa(pid - 1);
		ft_set_env(env, (t_hash_data){"$", p_id, HIDDEN});
		free(p_id);
    }
}


void sigint_handler(int signum)
{
	(void)signum;
	if (g_minishell_signal != SIGCHILD)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void sigquit_handler(int signum)
{
	(void)signum;
	if (g_minishell_signal == SIGCHILD)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
void ft_free_command(t_command *command);


void	ft_program(char **env)
{
	t_container		container;
	char 			*line;
	t_list_token	*list;

	list = NULL;
	g_global_state.heredoc_signal = -1;
	g_global_state.permission_status = 0;
	rl_catch_signals = 0;
	g_global_state.is_dir = 0;
	container.table = ft_create_symbol_table(env);
	g_global_state.argument = ft_get_env(container.table->env, "_");
	
	//finished testing of sort functionality of hash table!!!
	
	// ft_set_env(container.table->env, (t_hash_data){"a", "b", NORMAL});
	// ft_set_env(container.table->env, (t_hash_data){"d", "d", NORMAL});
	// ft_set_env(container.table->env, (t_hash_data){"v", "g", NORMAL});
	// ft_set_env(container.table->env, (t_hash_data){"b", NULL, NORMAL});
	// print_env(table, 1);
	// test for function table
	ft_get_pid(container, container.table->env);
	tcgetattr(STDIN_FILENO, &g_global_state.orig_termios);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	
	// rl_clear_signals();
	// char** env1 = ft_convert_env_to_args(table);
	// print_env_args(env1);
	while (1)
	{
		g_minishell_signal = SIGNORMAL;
		line = ft_get_line();
		if (!line)
		{
			exit(0);
		}
		if (!(*line))
		{
			free(line);
			continue;
		}
		int status = ft_balanced(line);
		if (status)
		{
			container.exit_status = status;
			char* st_status = ft_itoa(container.exit_status);
			ft_set_env(container.table->env, (t_hash_data){"?", st_status, HIDDEN});
			free(st_status);
			free(line);
			continue;
		}
		list = ft_tokenize(line, SEPARATORS);
		container = ft_parser(container, list);
		if (container.exit_status == SUCCESS_CODE)
			ft_executor(container.table, container);
		else
		{
			char* st_status = ft_itoa(container.exit_status);
			ft_set_env(container.table->env, (t_hash_data){"?", st_status, HIDDEN});
			free(st_status);
		}
		if (container.exec_type == LIST)
		{
			// ft_free_command(container.command);

		}
		else
		{
			// ft_free_tree(container.tree->ast_node);	
			// free(container.tree);
		}
		ft_free_list(list);
		free(line);
    }
    clear_history();
	ft_clear_symbol_table(container.table);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_program(env);
	return (0);	
}



// int main()
// {
	
// 	return (0);
// }




































// int main()
// {
// 	int fd = open("./valgrind.out", O_WRONLY);

// 	dup2(fd, 1);

// 	// system("ls");
// 	// printf("fileeeeee\n");

	
// }



































































































// (void)env;

	// t_list_token *list = ft_init_list();

	// ft_push_back(list, TEXT, "ls");
	// ft_push_back(list, PIPE, "|");
	// ft_push_back(list, TEXT, "pwd");
	// ft_push_back(list, PIPE, "|");
	// ft_push_back(list, TEXT, "grep");
	// ft_push_back(list, WRITE, ">");
	// ft_push_back(list, TEXT, "hello");

	// t_ast_node *tree = ft_shunting_yard_build_ast(list);

	// printf("trrr = %s\n", tree->token);


	// ft_print_list(list->head);
	// char* s = ft_strdup("");
	// ft_ast_print(tree,s, 0, 1);
	// free(s);
	
	
	// ft_free_list(list);

	// free(tree->token);
	// free(tree->subshell);
	// free(tree);
	
	// free(tree->left)
	// ft_free_tree(tree);


















































































































// #include <stdio.h>

// int main() {
//     FILE *file = fopen("example.txt", "r");
//     if (file == NULL) {
//         perror("Error opening file");
//         return 1;
//     }

//     int c;

//     // Loop to read characters until EOF is encountered
//     while ((c = fgetc(file)) != EOF) {
//         // Process the character, for example, print it
//         putchar(c);
//     }

//     // Check for EOF using feof
//     if (feof(file)) {
//         printf("\nEnd of file reached.\n");
//     } else {
//         printf("\nError reading file.\n");
//     }

//     // Close the file
//     fclose(file);

//     return 0;
// }



// #include <sys/mman.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <sys/mman.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     int fd = open("example.txt", O_RDONLY);
//     off_t file_size = lseek(fd, 0, SEEK_END);

//     // Map the file into memory
//     void *mapped_data = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

// 	if (mapped_data == MAP_FAILED) {
// 		perror("mmap");
// 		return (1);
//     }

//     // Use the mapped data...
//     printf("Contents of the mapped file:\n%s\n", (char*)mapped_data);

// 	(*(char*)mapped_data) = 'A';
//     // Unmap the file from memory
//     if (munmap(mapped_data, file_size) == -1) {
//         perror("munmap");
//         return 1;
//     }

//     // Close the file descriptor
//     close(fd);

//     return 0;
// }






















// #include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <errno.h>

// void	ft_can_reade(int fd)
// {
	
// }

// void	ft_can_write(int fd)
// {
	
// }

// ft_can_write_and_read(int fd)
// {
	
// }

// void ft_punic(const char *errorMessig)
// {
// 	if (errno == EACCES)
// 		perror("Permission denied Expands to: 13");
// 	else
// 		perror(errorMessig);
//     exit(EXIT_FAILURE);
// }

// int main(int ac, char **av)
// {
// 	int fd;
// 	int file_flag;
	
// 	fd = open(av[1], O_RDWR | O_TRUNC | O_CREAT, 0664);
// 	if (fd == -1)
// 		ft_punic("Error: Opening file Flags.");
// 	file_flag = fcntl(fd, F_GETFL);
// 	if (file_flag == -1)
// 		ft_panic("Error: Getting file flags");

// 	if (file_flag & O_RDONLY)
// 	{
// 		ft_can_reade(fd);
// 	}
// 	else if (file_flag & O_WRONLY)
// 	{
// 		ft_can_write(fd);
// 	}
// 	else if (file_flag & O_RDWR)
// 	{
// 		ft_can_write_and_read(fd);
// 	}


// 	//printf(EACCES);
	
	
// }

// #include <stdio.h>
// #include <dirent.h>

// int main()
// {
//     DIR *dir = opendir("/home/gevorg/Desktop/Minishell/Src/Executor");

//     if (dir == NULL)
// 	{
//         perror("Error opening directory");
//         return (1);
//     }

//     struct dirent *entry;
// 	// printf("###########################################################\n");
//     while ((entry = readdir(dir)) != NULL) {
//         // printf("%ld\n", entry->d_ino);
// 		printf("Name: %s, Offset: %ld\n", entry->d_name, (long)entry->d_off);
//     }
// 	// printf("###########################################################\n");
// 	// while ((entry = readdir(dir)) != NULL) {
//     //     printf("%s\n", entry->d_name);
//     // }
// 	// printf("###########################################################\n");
// 	// while ((entry = readdir(dir)) != NULL) {
//     //     printf("%ld\n", entry->d_off);
//     // }
// 	// printf("###########################################################\n");
// 	// while ((entry = readdir(dir)) != NULL) {
//     //     printf("%d\n", entry->d_reclen);
//     // }
// 	// printf("###########################################################\n");
// 	// while ((entry = readdir(dir)) != NULL) {
//     //     printf("%d\n", entry->d_type);
//     // }
// 	// printf("###########################################################\n");

//     closedir(dir);
//     return 0;
// }


// #include <stdio.h>
// #include <dirent.h>

// int main() {
//     const char *directory_path = "/path/to/your/directory";

//     DIR *dir = opendir(directory_path);

//     if (dir == NULL) {
//         perror("Error opening directory");
//         return 1;
//     }

//     struct dirent *entry;

//     // Read the first entry
//     entry = readdir(dir);

//     while (entry != NULL) {
//         printf("Name: %s, Offset: %ld\n", entry->d_name, (long)entry->d_off);

//         // Read the next entry using the offset
//         entry = readdir(dir);
//     }

//     closedir(dir);

//     return 0;
// }


































