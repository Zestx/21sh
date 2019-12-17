/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:14:02 by qbackaer          #+#    #+#             */
/*   Updated: 2019/12/17 19:07:04 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		ft_issquote(char c) {return (c == '\'');}
int		ft_isdquote(char c) {return (c == '\"');}

char	*get_full_squote(char *start)
{
	char	*full_quote;
	char	*end;

	end = start + 1;
	while (*end != '\'' && *end)
		end++;
	full_quote = strndup(start + 1, end - start - 1);
	return (full_quote);
}

char	*get_full_dquote(char *start)
{
	char	*full_quote;
	char	*end;

	end = start + 1;
	while (*end != '\"' && *end - 1 != '\\' && *end)
		end++;
	full_quote = strndup(start + 1, end - start - 1);
	return (full_quote);
}

char	*get_full_nword(char *start)
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

void	tokenize_input(char *input)
{
	char	*ptr;
	char	*curr_token;

	ptr = input;
	while (ptr < input + ft_strlen(input))
	{
		if (ft_isspacer(*ptr))
		{
			ptr++;
			continue ;
		}
		else if (ft_issquote(*ptr))
		{
			curr_token = get_full_squote(ptr);
			ptr = ptr + ft_strlen(curr_token) + 2;
		}
		else if (ft_isdquote(*ptr))
		{
			curr_token = get_full_dquote(ptr);
			ptr = ptr + ft_strlen(curr_token) + 2;
		}
		else
		{
			curr_token = get_full_nword(ptr);
			ptr = ptr + ft_strlen(curr_token);
		}
		printf("[%s]\n", curr_token);
		free(curr_token);
	}
}

int		main(void)
{
	char str[] = "Hi Im Quentin and \"This is full quote!\", the double type";

	tokenize_input(str);
	return (0);
}

