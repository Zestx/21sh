/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:16:05 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 19:17:22 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_tab(void)
{
	char	**tab;

	if (!(tab = malloc(sizeof(tab) * 2)))
		exit(EXIT_FAILURE);
	tab[0] = strdup_safe("");
	tab[1] = NULL;
	return (tab);
}

size_t	get_tab_size(char **tab)
{
	size_t	size;
	char	**roam;

	if (!tab)
		return (0);
	roam = tab;
	size = 0;
	while (*roam)
	{
		size++;
		roam++;
	}
	return (size);
}
