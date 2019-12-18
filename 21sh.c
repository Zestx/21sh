/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2019/12/18 16:49:59 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		main(void)
{
	char	**toks;
	char	**roam;
	char	*input;

	if (get_next_line(0, &input) < 0 || ft_strlen(input) < 2)
		return (-1);
	toks = tokenize_input(input);
	roam = toks;
	while (*roam)
	{
		printf("> %s\n", *roam);
		roam++;
	}
	return (0);
}
