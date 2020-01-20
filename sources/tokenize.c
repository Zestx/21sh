/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:35:59 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/20 20:25:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static char	*get_full_word(char	*start)
{
	char	*full_word;
	char	*end;
	int		esc;

	esc = 0;
	end = start + 1;
	while (*end && 
		  ((!is_redirection(end) && !is_quote(end) && *end != ';') || esc))
		end++;
	if (!(full_word = strndup(start + 1, end - start - 1)))
		exit(EXIT_FAILURE);
	return (full_word);
}

static char	*get_full_quote(char *start)
{
	char	*full_quote;
	char	*end;
	int		esc;

	end = start + 1;
	esc = 0;
	while (*end)
	{
		if (!esc && *end == '\"')
		{
			esc = 1;
			end++;
			continue ;
		}
		if (*end == *start && (*start == '\'' || !esc))
		{
			if (!(full_quote = strndup(start + 1, end - start - 1)))
				exit(EXIT_FAILURE);
			return (full_quote);
		}
	}
	return (NULL);
}


//This function retrieves a full token starting from *start and add it to
//the *toks linked list.
static t_tokens	*get_next_token(char **c, t_tokens *toks, int esc)
{
	char	*str;

	if (!esc && is_quote(*c))
	{
		str = get_full_quote(*c);
		toks = add_token_node(toks, str, QOT);
		*c += ft_strlen(str);
		free(str);
	}
	/*
	else if (!esc && is_redirection(**ptr));
	{
		//retrieve full redirection, add it to tokens list, advance c pointer.
	}*/
	else if (!esc && (**c == ';'))
	{
		toks = add_token_node(toks, ";", SCL);
		*c += 1;
	}
	else if (!ft_isspacer(**c))
	{
		str = get_full_word(*c);
		toks = add_token_node(toks, str, REG);
		*c += ft_strlen(str);
		free(str);
	}
	else 
		*c += 1;
	return (toks);
}

//Main function for lexing the input into a list of tokens.
t_tokens		*tokenize(char	*input)
{
	t_tokens	*toks;
	char		*ptr;
	int			esc;

	toks = NULL;
	esc = 0;
	ptr = input;
	while (*ptr)
	{
		while (ft_isspacer(*ptr))
			ptr++;
		if (!esc && *ptr == '\\')
		{
			esc = 1;
			ptr++;
			continue ;
		}
		toks = get_next_token(&ptr, toks, esc);
		esc = 0;
	}
	return (toks);
}
