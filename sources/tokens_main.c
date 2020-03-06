/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:35:59 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:01:55 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

void		fill_subtype(t_tokens *tok)
{
	if (!ft_strcmp(tok->string, ";"))
			tok->subtype = SMCL;
	if (!ft_strcmp(tok->string, "|"))
			tok->subtype = PIPE;
	if (ft_strchr(tok->string, '>') || ft_strchr(tok->string, '<'))
			tok->subtype = REDI;
}

t_tokens	*get_subtypes(t_tokens *toks)
{
	t_tokens	*curr_t;

	if (!toks)
		return (NULL);
	curr_t = toks;
	while (curr_t)
	{
		if (curr_t->type == OPER)
			fill_subtype(curr_t);
		curr_t = curr_t->next;
	}
	return (toks);
}

t_tokens	*tokenize(char *input)
{
	t_tokens	*toks;

	if (!input)
		return (NULL);
	toks = NULL;
	toks = get_next_token(input);
	toks = get_subtypes(toks);
	free(input);
	return (toks);
}
