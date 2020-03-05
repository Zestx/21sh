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

t_tokens	*tokenize(char *input)
{
	t_tokens	*toks;

	if (!input)
		return (NULL);
	toks = NULL;
	toks = get_next_token(input);
	free(input);
	return (toks);
}
