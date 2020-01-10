/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:20:25 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/10 20:15:03 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOSH_H
# define TOSH_H

# define REG 1
# define SQT 2
# define DQT 3
# define PIP 4
# define FSR 5
# define FDR 6
# define BSR 7
# define BDR 8
# define SCL 9

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
char		*trim_newlines(char *input);

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

#endif
