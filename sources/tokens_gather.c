/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gather.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:49:52 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 16:30:20 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

//count all the nodes of a certain type in a token list.
static size_t	count_spec_nodes(t_tokens *toks, int spec)
{
	size_t		count;
	t_tokens	*curr;

	if (!toks)
		return (0);
	curr = toks;
	count = 0;
	while (curr)
	{
		if (curr->type == spec)
			count++;
		curr = curr->next;
	}
	return (count);
}
//get all the redirections tokens of a list into another list.
t_tokens *gather_redir_tokens(t_tokens *group)
{
	t_tokens	*gathered;
	t_tokens	*curr;
	size_t		size;

	if (!group)
		return (NULL);
	size = count_spec_nodes(group, RED);
	if (!(gathered = malloc(sizeof(curr) * size)))
		exit(EXIT_FAILURE);
	gathered = NULL;
	curr = group;
	while (curr)
	{
		if (curr->type == RED)
			gathered = add_token_node(gathered, curr->string, RED);
		curr = curr->next;
	}
	return (gathered);
}

//get all the command/args (regulars and quotes) of a list into a table.
char **gather_cmds_tokens(t_tokens *group)
{
	char		**gathered;
	t_tokens	*curr;

	if (!group)
		return (NULL);
	gathered = NULL;
	curr = group;
	while (curr)
	{
		if (curr->type == REG || curr->type == QOT)
			gathered = ft_realloc_tab(gathered, curr->string);
		curr = curr->next;
	}
	return (gathered);
}
