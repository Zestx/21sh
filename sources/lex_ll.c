/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:49:43 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/06 18:40:44 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

t_tokens	*add_token_node(t_tokens *list, char *str, int tp)
{
	t_tokens *node;
	t_tokens *roam;

	if (!str || !ft_strlen(str))
		return (list);
	if (!(node = malloc(sizeof(t_tokens))))
		exit(EXIT_FAILURE);
	if (!(node->string = ft_strdup(str)))
		exit(EXIT_FAILURE);
	node->type = tp;
	node->next = NULL;
	if (!list)
		return (node);
	roam = list;
	while (roam->next)
		roam = roam->next;
	roam->next = node;
	return (list);
}

t_pnode		*add_pnode(t_pnode *list, char **args, t_tokens *redirs)
{
	t_pnode	*node;
	t_pnode *curr;

	if (!args && !redirs)
		return (list);
	if (!(node = malloc(sizeof(node))))
		exit(EXIT_FAILURE);
	node->cmds = args;
	node->reds = redirs;
	node->next = NULL;
	if (!list)
		return (node);
	curr = list;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	return (list);
}

size_t		count_nodes(t_tokens *list)
{
	size_t		i;
	t_tokens	*roam;

	if (!list)
		return (0);
	roam = list;
	i = 0;
	while (roam)
	{
		roam = roam->next;
		i++;
	}
	return (i);
}
