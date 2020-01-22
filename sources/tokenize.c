/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:35:59 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/22 14:38:38 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static char	*get_full_word(char	*start)
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


static char	*copy_dquote(char *start, int len)
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
		*c_ptr = *o_ptr;
		esc = 0;
		c_ptr++;
		o_ptr++;
	}
	*c_ptr = '\0';
	return (copy);
}

static char	*copy_squote(char *start, int len)
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

static char	*get_full_quote(char *start, int *og_len)
{
	char	*end;
	int		esc;

	end = start + 1;
	esc = 0;
	while (*end)
	{
		if (!esc && *end == '\\')
		{
			esc = 1;
			end++;
			continue ;
		}
		if ((*end == '\"' && !esc) || *end == '\'')
		{
			*og_len = end - start + 1;
			return (*end == '\"' ? copy_dquote(start + 1, get_dquote_len(start + 1))
			: copy_squote(start + 1, get_squote_len(start + 1)));
		}
		esc = 0;
		end++;
	}
	og_len = 0;
	return (NULL);
}

static t_tokens *add_singlechar_token(char *c, t_tokens *toks)
{
	if (*c == '|')
		toks = add_token_node(toks, "|", PIP);
	if (*c == ';')
		toks = add_token_node(toks, ";", SCL);
	if (*c == '~')
		toks = add_token_node(toks, "~", TIL);
	return (toks);
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

static t_tokens	*get_next_token(char *c, t_tokens *toks, int esc, int *og_len)
{
	char	*str;

	if (!esc && is_special(c))
		toks = get_special(c, toks, og_len);
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

//this function takes user input and returns a tokenized version in a linked list.
t_tokens		*tokenize(char	*input)
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
