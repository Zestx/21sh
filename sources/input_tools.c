/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:16:45 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/10 18:51:11 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	*trim_newlines(char *input)
{
	char	*start;
	char	*end;
	char	*trimed;

	if (!ft_strchr(input, '\n'))
		return (input);
	start = input;
	end = input + ft_strlen(input) - 1;
	while (*start == '\n')
		start++;
	while (*end == '\n')
		end--;
	if (!(trimed = malloc(end - start + 2)))
		exit(EXIT_FAILURE);
	while (*start)
	{
		*trimed = *start;
		trimed++;
		start++;
	}
	free(input);
	return (trimed);
}
