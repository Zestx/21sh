/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:16:45 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/13 15:02:31 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int		is_only_whitespaces(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (!ft_isspacer(*ptr))
			return (0);
	}
	return (1);
}
