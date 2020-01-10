/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:16:45 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/10 20:20:08 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	*trim_newlines(char *input)
{
	char	*trimmed;
	int	i;

	if (!(trimmed = malloc(ft_strlen(input) + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		trimmed[i] = input[i];
		i++;
	}
	trimmed[i] = '\0';
	free(input);
	return (trimmed);
}
