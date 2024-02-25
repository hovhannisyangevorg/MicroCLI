#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h" 

/**
 * Src/Builtin/ft_cd.c
 */
int	ft_cd(t_command* command, t_symbol_table* table);

/**
 * Src/Builtin/ft_echo.c
 */
int ft_echo(t_command *command, t_symbol_table* table);

/**
 * Src/Builtin/ft_env.c
 */
int	ft_env(t_command* command, t_symbol_table* table);

/**
 * Src/Builtin/ft_exit.c
 */
int	ft_exit(t_command *command, t_symbol_table* table);

/**
 * Src/Builtin/ft_export.c
 */
int	ft_export(t_command* command, t_symbol_table* table);

/**
 * Src/Builtin/ft_pwd.c
 */
int	ft_pwd(t_command* command, t_symbol_table* table);


/**
 * Src/Builtin/ft_unset.c
 */
int	ft_unset(t_command* command, t_symbol_table* table);

int	ft_history(t_command *command, t_symbol_table *table);


int         ft_ismultiply_overflow_u(long a, long b);
int         ft_isadd_overflow_u(long a, long b);
size_t      ft_atoll_util(size_t i, char *str, int *is_overflowed);
long long   ft_atoll(char *str, int *is_overflowed);


int     ft_is_valid_identifier(char *ident);
char	*ft_export_get_key(char *token, char *plus);
char	*ft_export_collect_data(char *line, t_hash_data *data, char *plus);

#endif