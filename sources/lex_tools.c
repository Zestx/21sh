/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:30:58 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/23 18:26:53 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int		ft_issquote(char c)
{
	return (c == '\'');
}

int		ft_isdquote(char c)
{
	return (c == '\"');
}

int		ft_isbquote(char c)
{
	return (c == '\\');
}

void	display_ll(t_tokens *toks)
{
	t_tokens	*ptr;
	int			n;

	if (!toks)
		return ;
	n = 0;
	ptr = toks;
	while (ptr)
	{
		printf("%d. [%s] ", n, ptr->string);
		if (ptr->type == 1)
			printf("REG\n");
		if (ptr->type == 2)
			printf("QOT\n");
		if (ptr->type == 3)
			printf("PIP\n");
		if (ptr->type == 4)
			printf("RED\n");
		if (ptr->type == 5)
			printf("SCL\n");
		ptr = ptr->next;
		n++;
	}
}

void	display_all_toks(t_tokens **all_toks)
{
	t_tokens	**curr;

	curr = all_toks;
	while (*curr)
	{
		printf("========================\n");
		display_ll(*curr);
		curr++;
	}
}




