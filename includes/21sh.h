/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:20:51 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 16:43:04 by qbackaer         ###   ########.fr       */
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
	char			**cmds;
	struct s_tokens *reds;
	struct s_pnode	*next;
}				t_pnode;

typedef struct	s_redirect
{
	char	*l_value;
	char	*r_value;
	char	*operand;
}		t_redirect;

/*
** display.c
*/
void		printenv(char **env);
void		prompt(void);
void		title(void);

/*
** execute_main.c
*/
void		execute_main(t_pnode *cmd_list);

/*
** input_main.c
*/
char		*get_input(void);
/*
** input_tools.c
*/
int			is_only_whitespaces(char *str);

/* 
** redirect_apply.c
*/
int			apply_output_redir
			(char *operand, char *l_value, char *r_value);
/* 
** redirect_parse.c
*/
void		redirect(t_tokens *redirections);

/*
** tokens_gather.c
*/
char 		**gather_cmds_tokens(t_tokens *group);
t_tokens	*gather_redir_tokens(t_tokens *group);

/*
** tokens_get.c
*/
t_tokens	*get_next_token(char *c, t_tokens *toks, int esc, int *og_len);

/*
** tokens_list.c
*/
t_tokens	*add_token_node(t_tokens *list, char *string, int type);
void		free_token_list(t_tokens *list);
t_pnode		*add_pnode(t_pnode *list, char **args, t_tokens *redirs);
void		free_pnode_list(t_pnode *list);
size_t		count_nodes(t_tokens *list);

/*
** tokens_main.c
*/
t_tokens	*tokenize(char *input);
char		*copy_dquote(char *start, int len);
char		*copy_squote(char *start, int len);
t_tokens	*add_singlechar_token(char *c, t_tokens *toks);

/*
** tokens_split.c
*/
t_tokens	**split_commands(t_tokens *toks, int splitter);

/*
** tokens_tools_a.c
*/
int			is_redirection(char *ptr);
int			is_quote(char *ptr);
int			get_dquote_len(char *start);
int			get_squote_len(char *start);
int			is_special(char *c);

/*
** tokens_tools_b.c
*/
char		*add_char(char *str, char c);
int			ft_issquote(char c);
int			ft_isdquote(char c);
int			ft_isbquote(char c);
void		display_ll(t_tokens *toks);

/*
** util_env.c
*/
char		*get_env_var(char **env, char *var_name);
char		**get_env(char **environ)

/*
** util_tab.c
*/
char		**init_tab(void)
size_t		get_tab_size(char **tab)
void		print_tab(char **tab)

#endif
