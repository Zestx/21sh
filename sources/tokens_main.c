/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:35:59 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:01:55 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char		*copy_dquote(char *start, int len)
{
	char	*copy;
	char	*o_ptr;
	char	*c_ptr;
	int		esc;

	if (!start)
		return (NULL);
	if (!(copy = malloc(len + 1)))
		exit(EXIT_FAILURE);
	o_ptr = start;
	c_ptr = copy;
	esc = 0;
	while (*o_ptr && (*o_ptr != '\"' || esc))
	{
		if (*o_ptr == '\\' && !esc)
		{
			esc = 1;
			o_ptr++;
			continue ;
		}
		*(c_ptr++) = *(o_ptr++);
		esc = 0;
	}
	*c_ptr = '\0';
	return (copy);
}

char		*copy_squote(char *start, int len)
{
	char	*copy;
	char	*o_ptr;
	char	*c_ptr;

	if (!start)
		return (NULL);
	if (!(copy = malloc(len + 1)))
		exit(EXIT_FAILURE);
	o_ptr = start;
	c_ptr = copy;
	while (*o_ptr && *o_ptr != '\'')
	{
		*c_ptr = *o_ptr;
		c_ptr++;
		o_ptr++;
	}
	*c_ptr = '\0';
	return (copy);
}

t_tokens	*add_singlechar_token(char *c, t_tokens *toks)
{
	if (*c == '|')
		toks = add_token_node(toks, "|", PIP);
	if (*c == ';')
		toks = add_token_node(toks, ";", SCL);
	return (toks);
}

t_tokens	*tokenize(char *input)
{
	t_tokens	*toks;
	char		*ptr;
	int			esc;
	int			og_len;

	og_len = 0;
	toks = NULL;
	esc = 0;
	ptr = input;
	while (*ptr)
	{
		while (ft_isspacer(*ptr))
			ptr++;
		if (!esc && *ptr == '\\')
			esc = 1;
		toks = get_next_token(ptr, toks, esc, &og_len);
		ptr += og_len;
		esc = 0;
	}
	return (toks);
}
