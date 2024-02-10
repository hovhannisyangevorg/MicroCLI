#include "shell.h"


t_symbol_table      *ft_create_symbol_table(char** env)
{
    t_symbol_table  *table;

    table = malloc(sizeof(t_symbol_table));

    table->env      = ft_create_env(env);
    table->function = ft_create_func_table();
    ft_set_env(table->env, (t_hash_data){"OLDPWD", NULL, EXPORT});
    return table;
}

void ft_clear_symbol_table(t_symbol_table* table)
{
    if (!table)
        return ;
    ft_free_hash_table(table->env);
    ft_clear_hash_table(table->env);
    ft_free_hash_table(table->function);
    ft_clear_hash_table(table->function);
    free(table);
}