/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:36:09 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/23 19:39:04 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static char		*get_full_word(char *start)
{
	char	*full_word;
	char	*end;
	int		esc;

	esc = 0;
	end = start;
	while (*end && ((!is_redirection(end) && !is_quote(end) &&
		!ft_isspacer(*end) && *end != ';') || esc))
		end++;
	if (!(full_word = strndup(start, end - start)))
		exit(EXIT_FAILURE);
	return (full_word);
}

static char		*get_full_quote(char *ptr, int *og_len)
{
	char	*end;
	int		esc;

	end = ptr + 1;
	esc = 0;
	while (*end)
	{
		if (!esc && *end == '\\')
		{
			esc = 1;
			end++;
			continue ;
		}
		if (*end == *ptr && (*ptr == '\'' || !esc))
		{
			*og_len = end - ptr + 1;
			return (*end == '\"' ? copy_dquote(ptr + 1, get_dquote_len(ptr + 1))
					: copy_squote(ptr + 1, get_squote_len(ptr + 1)));
		}
		esc = 0;
		end++;
	}
	og_len = 0;
	return (NULL);
}

static t_tokens	*get_special(char *c, t_tokens *toks, int *og_len)
{
	if (*c == '|' || *c == ';')
	{
		toks = add_singlechar_token(c, toks);
		*og_len = 1;
	}
	return (toks);
}

static t_tokens	*get_redirect(char *c, t_tokens *toks, int *og_len)
{
	char	*str;
	char	*c_ptr;

	if (!(str = malloc(5)))
		exit(EXIT_FAILURE);
	c_ptr = str;
	if (*c == '&' || ft_isdigit(*c))
		*(c_ptr++) = *(c++);
	if (*c == '>' || *c == '<')
		*(c_ptr++) = *(c++);
	if (*c == '>' || *c == '<' || *c == '&')
		*(c_ptr++) = *(c++);
	if (*c == '-' || ft_isdigit(*c))
		*(c_ptr++) = *(c++);
	*c_ptr = '\0';
	toks = add_token_node(toks, str, RED);
	*og_len = ft_strlen(str);
	return (toks);
}

t_tokens		*get_next_token(char *c, t_tokens *toks, int esc, int *og_len)
{
	char	*str;

	if (!esc && is_special(c))
	{
		toks = get_special(c, toks, og_len);
	}
	else if (!esc && is_redirection(c))
	{
		toks = get_redirect(c, toks, og_len);
	}
	else if (!esc && is_quote(c))
	{
		str = get_full_quote(c, og_len);
		toks = add_token_node(toks, str, QOT);
		free(str);
	}
	else
	{
		str = get_full_word(c);
		*og_len = ft_strlen(str);
		toks = add_token_node(toks, str, REG);
		free(str);
	}
	return (toks);
}
