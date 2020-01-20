/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:30:58 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/20 20:32:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

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
	t_tokens *ptr;

	if (!toks)
	{
		printf("list is null!\n");
		return ;
	}
	ptr = toks;
	while (ptr)
	{
		printf("[%s]\n", ptr->string);
		ptr = ptr->next;
	}
}
