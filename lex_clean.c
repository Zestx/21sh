/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:20:40 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/09 15:28:06 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"


//this function search for multiples bquotes in the input string and remove the extra.
char	*clean_bquotes(char *input)
{
	char	*cleaned_str;
	char	*ptr;

	if (!input)
		return (NULL);
}
