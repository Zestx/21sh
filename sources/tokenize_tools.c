/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:50:46 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/23 16:47:17 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int is_special(char *c)
{
	return ((*c == '|' && *(c + 1) != '|') || *c == ';');
}

int		is_redirection(char *ptr)
{
	if (*ptr == '<' || *ptr == '>')
		return (1);
	if (ft_isdigit(*ptr) && (*(ptr + 1) == '>' || *(ptr + 1) == '>'))
		return (1);
	if (*ptr == '&' && *(ptr + 1) == '>')
		return (1);
	return (0);
}

int		is_quote(char *ptr) 
{
	return (*ptr == '\'' || *ptr == '\"');
}

int	get_dquote_len(char *start)
{
	int		len;
	int		esc;
	char	*ptr;

	if (!start)
		return (0);
	ptr = start;
	esc = 0;
	len = 0;
	while (*ptr && (*ptr != '\"' || esc))
	{
		if (*ptr == '\\' && !esc)
		{
			esc = 1;
			ptr++;
			continue ;
		}
		esc = 0;
		len++;
		ptr++;
	}
	return (len);
}

int	get_squote_len(char *start)
{
	int		len;
	char	*ptr;

	if (!start)
		return (0);
	ptr = start;
	len = 0;
	while (*ptr && *ptr != '\'')
	{
		ptr++;
		len++;
	}
	return (len);
}
