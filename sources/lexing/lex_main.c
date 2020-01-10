/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:14:02 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/10 16:28:18 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

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

	end = start + 1;
	while (*end)
	{
		if (ft_isdquote(*end))
			break;
		if (*end)
			end++;
	}
	full_quote = strndup(start + 1, end - start - 1);
	return (full_quote);
}

char		*get_full_rword(char *start)
{
	char	*full_word;
	char	*end;

	end = start + 1;
	while (!ft_isspacer(*end) && !ft_issquote(*end)
			&& !ft_isdquote(*end) && *end != '|'
			&& *end != '>' && *end != '<' && *end)
		end++;
	full_word = strndup(start, end - start);
	return (full_word);
}

int			is_splitter(char c) 
{
	return (c == '|' || c== '>' || c == '<');
}

t_tokens	*tokenize_input(char *input)
{
	char		*ptr;
	t_tokens	*toks;

	toks = NULL;
	ptr = input;
	while (ptr < input + ft_strlen(input))
	{
		if (ft_isspacer(*ptr))
		{
			ptr++;
			continue;
		}
		else if (ft_issquote(*ptr))
		{
			toks = add_token_node(toks, get_full_squote(ptr), SQT);
			ptr = ptr + ft_strlen(get_full_squote(ptr)) + 2;
		}
		else if (ft_isdquote(*ptr))
		{
			toks = add_token_node(toks, get_full_dquote(ptr), DQT);
			ptr = ptr + ft_strlen(get_full_dquote(ptr)) + 2;
		}
		else if (*ptr == '|')
		{
			toks = add_token_node(toks, "|", PIP);
			ptr++;
		}
		else if (*ptr == '>' && *(ptr + 1) == '>')
		{
			toks = add_token_node(toks, ">>", FDR);
			ptr += 2;
		}
		else if (*ptr == '>')
		{
			toks = add_token_node(toks, ">", FSR);
			ptr++;
		}
		else if (*ptr == '<' && *(ptr + 1) == '<')
		{
			toks = add_token_node(toks, "<<", BDR);
			ptr += 2;
		}
		else if (*ptr == '<')
		{
			toks = add_token_node(toks, "<", BSR);
			ptr++;
		}
		else
		{
			toks = add_token_node(toks, get_full_rword(ptr), REG);
			ptr = ptr + ft_strlen(get_full_rword(ptr));
		}
	}
	return (toks);
}
