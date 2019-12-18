/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:20:25 by qbackaer          #+#    #+#             */
/*   Updated: 2019/12/18 18:33:44 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOSH_H
# define TOSH_H

# define REG 1
# define SQT 2
# define DQT 3

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct	s_tokens
{
		char			*string;
		int				type;
		struct s_tokens	*next;
}				t_tokens;

/*
** 21sh.c
*/


/*
** lex_main.c
*/
t_tokens	*tokenize_input(char *input);
char		*get_full_nword(char *start);
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
