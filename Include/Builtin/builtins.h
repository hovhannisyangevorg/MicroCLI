#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h" 

int	ft_exit(t_command *command, t_symbol_table* table);
int ft_echo(t_command *command, t_symbol_table* table);
int	ft_unset(t_command* command, t_symbol_table* table);
int	ft_pwd(t_command* command, t_symbol_table* table);
int	ft_cd(t_command* command, t_symbol_table* table);
int	ft_env(t_command* command, t_symbol_table* table);
int	ft_export(t_command* command, t_symbol_table* table);
int ft_test(t_command *command, t_symbol_table *table);

#endif