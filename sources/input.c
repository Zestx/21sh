/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:45:23 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/10 18:51:39 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static char	*is_quote_closed(char *start)
{
	char	*end;
	int		bs_c;

	end = start + 1;
	while (*end)
	{
		bs_c = 0;
		while (*end == '\\')
		{
			bs_c++;
			end++;
		}
		if (*end == *start && (bs_c % 2 == 0 || *start != '\"'))
			return (end);
		end++;
	}
	return (NULL);
}

static int	check_quotes(char *str)
{
	char	*ptr;
	int		bs_c;

	ptr = str;
	while (*ptr)
	{
		bs_c = 0;
		while (*ptr == '\\')
		{
			bs_c++;
			ptr++;
		}
		if ((*ptr == '\"' && bs_c % 2 == 0) || *ptr == '\'')
		{
			if (!is_quote_closed(ptr))
				return (0);
			else
				ptr = is_quote_closed(ptr);
		}
		ptr++;
	}
	return (1);
}

static int	is_input_done(char *str)
{
	if (!check_quotes(str))
		return (0);
	if (str[ft_strlen(str) - 1] == '\\')
		return (0);
	// need to also check for unfinished pipe or redirection
	return (1);
}

static int	syntax_check(char *str)
{
	char	*chr;

	if ((chr = ft_strchr(str, ';')) && (*(chr + 1) == ';'))
	{
		ft_putendl_fd("21sh: parsing error: unexpected ';'", 2);
		return (0);
	}
	return (1);
}

char		*get_input(void)
{
	char	*input;
	char	*temp;

	if (get_next_line(0, &input) < 0)
		exit(EXIT_FAILURE);
	//input = trim_newlines(input);
	if (input && ft_strlen(input) && !syntax_check(input))
	{
		free(input);
		return(NULL);
	}
	while (!is_input_done(input))
	{
		ft_putstr("\\ ");
		if (get_next_line(0, &temp) < 0)
			exit(EXIT_FAILURE);
		input = ft_strjoin(input, temp);
		free(temp);
	}
	return (input);
}
