/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gevorg <gevorg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:23:33 by gehovhan          #+#    #+#             */
/*   Updated: 2024/01/20 18:03:30 by gevorg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef TOKENIZER_H
# define TOKENIZER_H

# include "shell.h"

t_stack 		*ft_initialize_stack();
t_list_token 	*ft_multi_split(char* str, char* delims, int issub);
int 			ft_is_empty(t_stack *stack);
void			ft_push_stack(t_stack *stack, char item);
char 			ft_pop_stack(t_stack *stack);
void 			ft_free_stack(t_stack *stack);
int             ft_balanced(char *line);
t_list_token 	*ft_init_list();
void			ft_push_back(t_list_token *list, int type, const char *token);
void			ft_push_front(t_list_token *list, int type, const char *token);
void			ft_pop_back(t_list_token *list);
void			ft_pop_front(t_list_token *list);
void			ft_free_list(t_list_token *list);
void			ft_print_list(t_token* list);
char			*ft_get_line();
void			sig_handler_c(int signum);
void 			ft_ordering(t_list_token *list);
void 			ft_init_token(t_token *node, int type, char *elem);
void			ft_split_token(t_list_token *list);


// ft_types.c
char*           ft_get_type(t_token_type type);

t_token_type    ft_get_type_map(int type);

int             ft_isoperator(t_token_type type);

int				ft_iscommand(t_token_type type);

int             ft_is_redirection(t_token_type type);

int             ft_is_breckets(t_token_type type);

int             ft_is_special_node(t_token_type type);

// ft_list_helpers.c
t_list_token*   ft_sublist(t_token* start, t_token* end);

t_token*        ft_find_list(t_token_type type, t_token* start);

t_token*	    ft_find_close_list(t_token* open);


// ft_tokenizer.c
int             ft_ignore_quots(char *str, char quot, size_t i);

char            *ft_tokenize_with_space(char *str, int* type);

char            *ft_tokenize_with_delims(char *str,  char *delim, int* type);

t_list_token*   ft_tokenize_string_space(char *input);

t_list_token*   ft_tokenize(char *input, char* delims);

#endif
