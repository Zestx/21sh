/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:49:43 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 15:44:09 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

t_tokens	*add_token_node(t_tokens *list, char *str, int tp, int sub)
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
	node->subtype = sub;
	node->next = NULL;
	if (!list)
		return (node);
	roam = list;
	while (roam->next)
		roam = roam->next;
	roam->next = node;
	return (list);
}

void		free_token_list(t_tokens *list)
{
	t_tokens *tmp;
	t_tokens *ptr;

	if (!list)
	{
		ft_putendl_fd("free_token_list error: NULL list.", 2);
		return ;
	}
	ptr = list;
	while (ptr)
	{
		tmp = ptr->next;
		if (ptr->string)
			free(ptr->string);
		free(ptr);
		ptr = tmp;
	}
}

void		free_token_group(t_tokens **list)
{
	t_tokens	**curr;

	if (!list)
		return ;
	curr = list;
	while (*curr)
	{
		curr++;
	}
	return ;
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
