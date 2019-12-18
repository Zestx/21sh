/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2019/12/18 18:34:42 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		main(void)
{
	t_tokens	*toks;
	t_tokens	*roam;
	char		*input;

	if (get_next_line(0, &input) < 0 || ft_strlen(input) < 2)
		return (-1);
	toks = tokenize_input(input);
	roam = toks;
	printf("Number of tokens: [%zu]\n", count_nodes(toks));
	while (roam)
	{
		printf("> %s\n", roam->string);
		roam = roam->next;
	}
	return (0);
}
