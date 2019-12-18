/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:20:25 by qbackaer          #+#    #+#             */
/*   Updated: 2019/12/18 17:41:25 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft/libft.h"

/*
** 21sh.c
*/

/*
** lex_main.c
*/
char	**tokenize_input(char *input);
char	*get_full_nword(char *start);
char	*get_full_dquote(char *start);
char	*get_full_squote(char *start);

/* 
** lex_tools.c
*/
int		ft_issquote(char c);
int		ft_isdquote(char c);
int		ft_isbquote(char c);
