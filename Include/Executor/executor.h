#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <sys/stat.h>

# include 	"shell.h"

/**
 * Src/Executor/ft_casts.c
 */
t_function_entity	*ft_entity_to_function(t_hash_entity *hash);
t_env_entity		*ft_entity_to_env(t_hash_entity *hash);
t_hash_entity		*ft_function_to_entity(t_function_entity *func);
t_hash_entity		*ft_env_to_entity(t_env_entity *env);

/**
 * Src/Executor/ft_command_path.c
 */
int		ft_command_path(t_command *command, t_hash_table *env);

/**
 * Src/Executor/ft_control_pipe.c
 */
void	ft_hendle_pipe(t_vector * pipe_fd, size_t pipe_iter, t_io io);
void	ft_handle_redirect_ios(t_io io);
char	*ft_get_last_arg(t_command* command);
int		ft_open_process_for_pipe(t_ast_node *tree, t_process_info *info, size_t* pipe_iter);
void	ft_execute_part(t_ast_node *tree, t_process_info *info, size_t* pipe_iter);

/**
 * Src/Executor/ft_executor_with_list.c
 */
void	ft_restore_std_io(t_io io);
int     ft_handle_external(t_process_info *info);
int		ft_executor_with_list(t_io io, t_command *command, t_symbol_table* table);

/**
 * Src/Executor/ft_executor_with_tree.c
 */
size_t	ft_pipe_count_tree(t_ast_node *tree);

/**
 * Src/Executor/ft_executor.c
 */
int		ft_execute_command(t_process_info *info);
void	ft_executor(t_symbol_table *table, t_container cont);
void    ft_handle_child_process(t_process_info *info, int is_pipe);

/**
 * Src/Executor/ft_expand_env.c
 */
int		ft_ignore_symbol(char *str, char sym, size_t i);
size_t	ft_size_variable_$(char *arg, t_symbol_table *symbol_table);
size_t	ft_count_replace_len(char *arg, t_symbol_table *symbol_table, t_expand_type isexpand);
size_t	ft_vulue_variable_$(char *arg, char *expand, t_symbol_table *symbol_table);
int		ft_variable_identifier(char *ident);
char	*ft_count_replace(char *arg, t_symbol_table *symbol_table, t_expand_type isexpand);
void 	ft_expand_env(t_command *command, t_symbol_table *table);

/**
 * Src/Executor/ft_file_method.c
 */
void	    ft_open_file(t_process_info *info, t_vector* fd_vector);
t_vector	ft_open_pipe_fd(size_t pipe_count);
void	    ft_open_all_fd(t_ast_node *ast_node, t_process_info *info);
void		ft_close_fd(t_vector *fd_vector);
void	    ft_open_type(t_redirect *redirect, t_process_info *info, t_vector *fd_vector);


/**
 * Src/Executor/ft_hash_table.c
 */
int					ft_partition(char **arr, int low, int high);
void				ft_quicksort(char **arr, int low, int high);
t_hash_table_arr 	ft_sort_env(t_hash_table *table);
t_entity_table		*ft_init_entity_table(size_t initialCapacity, t_hash_type type);
t_hash_table		*ft_init_hash_table(size_t initialCapacity, t_hash_type type);
void				ft_init_entity_list(t_hash_entity_list *list);
size_t				ft_hash_entity(size_t capacity, char *key);
t_function_entity	*ft_create_function_entity(char *key, void *data);
t_env_entity		*ft_create_env_entity(t_hash_data data);
void				ft_push_entity(t_hash_entity_list *lst, t_hash_data data, t_hash_type type);
void				ft_resize_entity(t_hash_table *table, size_t new_capacity);
void				ft_insert_entity(t_hash_table *table, t_hash_data data);
t_function_callback	ft_get_function(t_hash_table *table, char *key);
t_function_entity	*ft_get_function_entity(t_hash_table *table, char *key);
t_env_entity		*ft_get_env_entity(t_hash_table *table, char *key);
char				*ft_get_env(t_hash_table *table, char *key);
void				ft_set_env(t_hash_table *table, t_hash_data data);
void				print_env(t_hash_table* env, t_visibility_type visibility);
t_hash_table		*ft_create_env(char **env);
t_hash_table		*ft_create_func_table();
void				ft_pop_entity(t_hash_table *table, char *key);
t_hash_table_arr	ft_convert_env_to_args(t_hash_table* env, t_visibility_type visibility, int mode);
void				ft_free_hash_table(t_hash_table* table);
void                print_env_table(t_hash_table_arr arr);
void				ft_clear_hash_table(t_hash_table* table);

/**
 * Src/Executor/ft_heredoc.c
 */
int					ft_isquot(const char *end_of_file);
char				*ft_generate_filename();
size_t				ft_EOF_length(char *end_of_file);
char				*ft_ignor_EOF_quots(char *end_of_file);
char				*ft_substr_c(char *line, char c);
void				ft_replace_all(char **line, char *src_env, char *chang_env);
void				ft_hendle_env_variable(char **line, t_hash_table *env);
int					open_heredoc(t_redirect	*red, t_hash_table *env);

/**
 * Src/Executor/ft_signals.c
 */
void				sigint_handler(int signum);
void				ft_sigquit_handler(int signum);
void				ft_child_sigint(int num);
void				ft_heredoc_signal(int num);

/**
 * Src/Executor/ft_symbol_table.c
 */
t_symbol_table      *ft_create_symbol_table(char** env);
void				ft_clear_symbol_table(t_symbol_table* table);

/**
 * Src/Executor/ft_vector_method.c
 */
void	ft_init_arrey(t_vector *tab, size_t size);
void	ft_push_arrey(t_vector *tab, int val);

#endif