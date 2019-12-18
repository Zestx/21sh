/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:14:02 by qbackaer          #+#    #+#             */
/*   Updated: 2019/12/18 18:31:12 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*get_full_squote(char *start)
{
	char	*full_quote;
	char	*end;

	end = start + 1;
	while (*end != '\'' && *end)
		end++;
	full_quote = strndup(start + 1, end - start - 1);
	return (full_quote);
}

char		*get_full_dquote(char *start)
{
	char	*full_quote;
	char	*end;
	int		i;

	end = start + 1;
	while (*end)
	{
		i = 0;
		while (*end && ft_isbquote(*end))
		{
			end++;
			i++;
		}
		if (!(i % 2) && ft_isdquote(*end))
			break;
		if (*end)
			end++;
	}
	full_quote = strndup(start + 1, end - start - 1);
	return (full_quote);
}

char		*get_full_nword(char *start)
{
	char	*full_word;
	char	*end;

	end = start + 1;
	while (!ft_isspacer(*end) && !ft_issquote(*end)
			&& !ft_isdquote(*end) && *end)
		end++;
	full_word = strndup(start, end - start);
	return (full_word);
}

t_tokens	*tokenize_input(char *input)
{
	char		*ptr;
	t_tokens	*toks;

	toks = NULL;
	ptr = input;
	while (ptr < input + ft_strlen(input))
		if (ft_isspacer(*ptr))
		{
			ptr++;
			continue;
		}
		else if (ft_issquote(*ptr))
		{
			toks = add_token_node(toks, get_full_squote(ptr), 2);
			ptr = ptr + ft_strlen(get_full_squote(ptr)) + 2;
		}
		else if (ft_isdquote(*ptr))
		{
			toks = add_token_node(toks, get_full_dquote(ptr), 3);
			ptr = ptr + ft_strlen(get_full_dquote(ptr)) + 2;
		}
		else
		{
			toks = add_token_node(toks, get_full_nword(ptr), 1);
			ptr = ptr + ft_strlen(get_full_nword(ptr));
		}
	return (toks);
}
