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

#endif