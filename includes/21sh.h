/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:20:25 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/21 19:40:58 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOSH_H
# define TOSH_H

# define REG 1
# define QOT 2
# define PIP 3
# define ORD 4
# define IRD 5
# define SCL 6
# define TIL 7

# define MAG "\x1B[35m"
# define CYAN "\x1B[36m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct	s_tokens
{
		char			*string;
		int				type;
		struct s_tokens	*next;
}				t_tokens;

/*
** input.c
*/
char		*get_input(void);

/*
** input_tools.c
*/
int			is_only_whitespaces(char *str);

/*
** tokenize.c
*/
t_tokens	*tokenize(char *input);

/*
** tokenize_tools.c
*/
int			is_redirection(char *ptr);
int			is_quote(char *ptr);
int			get_dquote_len(char *start);
int			get_squote_len(char *start);
int			is_special(char *c);

/*
** util_env.c
*/
char		*get_env_var(char **env, char *var_name);

/*
** display.c
*/
void		title(void);
void		prompt(void);
void		printenv(char **env);

/*
** lex_main.c
*/
t_tokens	*tokenize_input(char *input);
char		*get_full_rword(char *start);
char		*get_full_dquote(char *start);
char		*get_full_squote(char *start);

/*
** lex_list.c
*/
t_tokens	*add_token_node(t_tokens *list, char *string, int type);
size_t		count_nodes(t_tokens *list);

/* 
** lex_tools.c
*/
int		ft_issquote(char c);
int		ft_isdquote(char c);
int		ft_isbquote(char c);
void	display_ll(t_tokens *toks);

#endif
