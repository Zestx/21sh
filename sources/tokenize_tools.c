/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:50:46 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/20 20:20:40 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int		is_redirection(char *ptr)
{
	if (*ptr == '<' || *ptr == '>')
		return (1);
	if (ft_isdigit(*ptr) && (*(ptr + 1) == '>' || *(ptr + 1) == '>'))
		return (1);
	if (*ptr == '&' && *(ptr + 1) == '>')
		return (1);
	if (*ptr == '|' && *(ptr + 1) != '|')
		return (1);
	return (0);
}

int		is_quote(char *ptr) 
{
	return (*ptr == '\'' || *ptr == '\"');
}
