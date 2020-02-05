/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:20:51 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/05 20:09:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOSH_H
# define TOSH_H

# define REG 1
# define QOT 2
# define PIP 3
# define RED 4
# define SCL 5
# define TIL 6

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

typedef struct	s_pnode
{
	t_commands		*args;
	t_redirs		*reds;
	struct s_pnode	*next;
}				t_pnode;

typedef struct	s_redirs
{
	char			from;
	char			to;
	struct s_redirs	*next;
}				t_redirs;

typedef struct	s_commands;
{
	char				*string;
	struct s_command	*next;
}				t_commands;


/*
 * ** split_commands.c
 * */
t_tokens	**split_commands(t_tokens *toks, int splitter);

/*
 * ** input.c
 * */
char		*get_input(void);

/*
 * ** input_tools.c
 * */
int			is_only_whitespaces(char *str);

/*
 * ** tokenize.c
 * */
t_tokens	*tokenize(char *input);

/*
 * ** tokenize_tools.c
 * */
int			is_redirection(char *ptr);
int			is_quote(char *ptr);
int			get_dquote_len(char *start);
int			get_squote_len(char *start);
int			is_special(char *c);

/*
 * ** get_tokens.c
 * */
t_tokens	*get_next_token(char *c, t_tokens *toks, int esc, int *og_len);
char		*copy_dquote(char *start, int len);
char		*copy_squote(char *start, int len);
t_tokens	*add_singlechar_token(char *c, t_tokens *toks);

/*
 * ** util_env.c
 * */
char		*get_env_var(char **env, char *var_name);

/*
 * ** display.c
 * */
void		title(void);
void		prompt(void);
void		printenv(char **env);

/*
 * ** lex_list.c
 * */
t_tokens	*add_token_node(t_tokens *list, char *string, int type);
size_t		count_nodes(t_tokens *list);

/* 
 * ** lex_tools.c
 * */
int		ft_issquote(char c);
int		ft_isdquote(char c);
int		ft_isbquote(char c);
void		display_ll(t_tokens *toks);
void		display_all_toks(t_tokens **toks);
#endif
