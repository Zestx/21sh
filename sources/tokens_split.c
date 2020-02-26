/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:13:03 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:04:39 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static size_t	get_groups_number(t_tokens *toks, int splitter)
{
	t_tokens	*curr;
	size_t		n;

	curr = toks;
	n = 1;
	while (curr)
	{
		if (curr->type == splitter && curr->next)
			n++;
		curr = curr->next;
	}
	return (n);
}

static t_tokens	**init_tokens_groups(size_t size)
{
	t_tokens **toks_groups;

	if (!(toks_groups = malloc(sizeof(toks_groups) * size + 1)))
		exit(EXIT_FAILURE);
	while (size + 1)
	{
		toks_groups[size] = NULL;
		size--;
	}
	return (toks_groups);
}

void		display_split(t_tokens **groups)
{
	t_tokens **curr;

	if (!groups)
		return ;
	curr = groups;
	while (*curr)
	{
		display_ll(*curr);
		curr++;
	}
	return ;
}

t_tokens		**split_commands(t_tokens *toks, int splitter)
{
	t_tokens	**toks_groups;
	t_tokens	*curr_list;
	t_tokens	**curr_group;

	if (!toks)
		return (NULL);
	toks_groups = init_tokens_groups(get_groups_number(toks, splitter));
	curr_list = toks;
	curr_group = toks_groups;
	while (curr_list)
	{
		if (curr_list->type != splitter)
		{
			*curr_group =
				add_token_node(*curr_group, curr_list->string, curr_list->type);
		}
		else
			curr_group++;
		curr_list = curr_list->next;
	}
	free_token_list(toks);
	return (toks_groups);
}
