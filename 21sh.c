/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/09 15:41:38 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		display_args(t_tokens *args)
{
	t_tokens *roam;
	if (!args)
	{
		printf("empty list.\n");
		return 0;
	}
	roam = args;
	while (roam)
	{
		if (roam->type == 1)
			printf("[REG] ");
		if (roam->type == 2)
			printf("[SQT] ");
		if (roam->type == 3)
			printf("[DQT] ");
		if (roam->type == 4)
			printf("[PIP] ");
		if (roam->type == 5)
			printf("[FSR] ");
		if (roam->type == 6)
			printf("[FDR] ");
		if (roam->type == 7)
			printf("[BSR] ");
		if (roam->type == 8)
			printf("[BDR] ");
		printf("%s\n", roam->string);
		roam = roam->next;
	}
	return (1);
}


int		main(void)
{
	t_tokens	*toks;
	char		*input;

	title();
	while (1)
	{
		prompt();
		if (get_next_line(0, &input) < 0 || ft_strlen(input) < 2)
			return (-1);
		toks = tokenize_input(input);
		display_args(toks);
	}
	return (0);
}
