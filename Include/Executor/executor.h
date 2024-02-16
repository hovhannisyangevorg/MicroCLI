#ifndef EXECUTOR_H
# define EXECUTOR_H

# include 	"shell.h"


void ft_executor(t_symbol_table* table, t_container cont);

void	ft_open_file(t_command *command, t_hash_table *env, t_vector* fd_vector, t_io io);
int     ft_executor_with_list(t_io io, t_command *command, t_symbol_table* table);
int		ft_command_fron_PATH(t_command *command, t_hash_table *env);
void	ft_open_type(t_redirect *redirect, t_command *cmd, t_vector *fd_vector, t_hash_table *env, t_io io);
void	ft_close_fd(t_vector *fd_vector);
void    ft_handle_redirect_ios(t_io io);
void    ft_restore_std_io(t_io io);
t_io    ft_init_io_restore(t_io io);


// ft_casts.c
t_function_entity	*ft_entity_to_function(t_hash_entity *hash);
t_env_entity		*ft_entity_to_env(t_hash_entity *hash);
t_hash_entity		*ft_function_to_entity(t_function_entity *func);
t_hash_entity		*ft_env_to_entity(t_env_entity *env);
t_symbol_table      *ft_create_symbol_table(char** env);
void                ft_clear_symbol_table(t_symbol_table* table);
void				ft_set_env(t_hash_table *table, t_hash_data data);

// ft_hash_table.c
void				ft_pop_entity(t_hash_table *table, char *key);
void				ft_free_hash_table(t_hash_table* table);
void				ft_clear_hash_table(t_hash_table* table);
t_hash_table		*ft_init_hash_table(size_t initialCapacity, t_hash_type type);
void				ft_init_entity_list(t_hash_entity_list *list);
t_hash_table_arr    ft_sort_env(t_hash_table* table);
t_hash_table*       ft_create_func_table();
// void				ft_init_entity_list2(t_hash_entity_list *lhs, t_hash_entity_list *rhs);
size_t				ft_hash_entity(size_t capacity, char *key);
t_function_entity	*ft_create_function_entity(char *key, void *data);
t_env_entity		*ft_create_env_entity(t_hash_data data);
void                ft_push_entity(t_hash_entity_list *lst, t_hash_data data, t_hash_type type);
void				ft_resize_entity(t_hash_table *table, size_t new_capacity);
void				ft_insert_entity(t_hash_table *table, t_hash_data data);
t_function_callback	ft_get_function(t_hash_table *table, char *key);
char				*ft_get_env(t_hash_table *table, char *key);
t_env_entity	    *ft_get_env_entity(t_hash_table *table, char *key);
void				print_env(t_hash_table *env, t_visibility_type type);
t_hash_table		*ft_create_env(char **env);

void				ft_init_arrey(t_vector *tab, size_t size);
void				ft_push_arrey(t_vector *tab, int val);
int					ft_isquot(const char *exit_key);

t_vector			ft_open_pipe_fd(size_t pipe_count);
// void				ft_assign_pipe_fd(t_io io, t_ast_node *tree, t_vector *pipe_fd, size_t* pipe_iter);

void				ft_execute_part(t_io io, t_ast_node *tree, t_symbol_table* table, t_vector *pipe_fd, size_t* pipe_iter);
t_hash_table_arr    ft_convert_env_to_args(t_hash_table* env, t_visibility_type type);
void                print_env_table(t_hash_table_arr arr);

char				*ft_count_replace(char *arg, t_symbol_table *symbol_table, t_expand_type isexpand);




void				ft_free_tree(t_ast_node *tree);


void sigint_handler(int signum);
void sigquit_handler(int signum);
void ft_child_sigint(int num);

#endif