/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:45:23 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/13 15:22:23 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

//This function check if the quote starting at 'start' is ever closing or not
static char		*is_quote_closed(char *start)
{
	char	*end;
	int		esc;

	esc = 0;
	end = start + 1;
	while (*end)
	{
		if (!esc && *end == '\\')
		{
			esc = 1;
			end++;
			continue ;
		}
		if (*end == *start && (*start == '\'' || !esc))
			return (end);
		esc = 0;
		end++;
	}
	return (NULL);
}

//This function check if the current input is complete.
static int		is_input_done(char *str)
{
	int			esc;
	char		*ptr;

	ptr = str;
	esc = 0;
	while (*ptr)
	{
		//is *ptr an escape backslash? If so, 'esc' is turned to 1
		if (!esc && *ptr == '\\')
		{
			esc = 1;
			ptr++;
			continue ;
		}
		//is *ptr a quote character? If so, check if it's closed
		if (!esc && (*ptr == '\"' || *ptr == '\''))
			if (!(ptr = is_quote_closed(ptr)))
				return (0);
		//is *ptr a pipe? If so, check if there's something after it
		if (!esc && *ptr == '|' && is_only_whitespaces(ptr + 1))
			return (0);
		esc = 0;
		ptr++;
	}
	//is there an escape at the end of the line?
	if (ft_strlen(str) && *(ptr - 1) == '\\')
		return (0);
	return (1);
}

//This functions keep getting lines from user as long as the command
//is incomplete (unclosed quotes, backslash at the end, pipes going nowhere..)
static char		*get_all_lines(void)
{
	char		*full_input;
	char		*line;
	char		*temp;

	full_input = NULL;
	while (1)
	{
		//get a line and trim it
		if (get_next_line(0, &line) < 0)
			exit(EXIT_FAILURE);
		temp = line;
		line = ft_strtrim(line);
		free(temp);
		//add it to the current full input
		temp = full_input;
		if (!(full_input = ft_strjoin(full_input, line)))
			exit(EXIT_FAILURE);
		free(temp);
		free(line);
		//check if the input is closed and done. 
		//If so, leave the loop and return it.
		if (is_input_done(full_input))
			break ;
	}
	return (full_input);
}

//Main function for getting the user input.
char			*get_input(void)
{
	char		*input;

	//get the full user input, then tokenize it.
	input = get_all_lines();
	return (input);
}
