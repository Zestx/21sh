/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:45:23 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/10 16:28:14 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int	are_quotes_closed(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '\"' || *ptr == '\'')
			//check if closed. if it is, jump to the end of it.
			//if it's not, return 0.
		ptr++;
	}
}

static int	is_input_closed(char *str)
{
	//check for unclosed quotes
	if (!are_quotes_closed(str))
		return (0);
	//check for unfinished pipe
	//	return (0);
	//check for backslash at the end
	//	return (0);
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
	char	*chr;

	if (get_next_line(0, &input) < 0)
		exit(EXIT_FAILURE);
	if (input && ft_strlen(input) && !syntax_check(input))
	{
		free(input);
		return(NULL);
	}
	//while the input is not finished (unclosed quote, unfinished pipe, etc..)
	//the user is prompted to complete it.
	while (!is_input_closed(input))
	{
		ft_putstr("\ ");
		if (get_next_line(0, &temp) < 0)
			exit(EXIT_FAILURE);
		input = ft_strjoin(input, temp);
		free(temp);
	}
	return (input);
}
