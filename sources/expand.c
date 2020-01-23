/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:49:34 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/23 16:43:49 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "../includes/21sh.h"

//this function roam through the token list and expand what needs to be expanded.
t_tokens	*roam_expand(t_tokens	*toks, char	**env)
{
	char	**ptr;

	if (!toks)
		return (NULL);
	ptr = toks;
	while (ptr)
	{
		if (ptr->type == REG)
		{
			printf("%s is regular.\n", ptr->string);
		}
		ptr = ptr->next;
	}
	return (NULL);
}*/
