/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:35:59 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/13 18:37:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

//This function retrieves a full token starting from *start and add it to
//the *toks linked list.
static t_tokens	*get_next_token(char **c, t_tokens *toks, int esc)
{
	//is it a quote?
	if (!esc && (**c == '\'' || **c == '\"'')
		t_tokens = get_full_quote("<F12>")
	//is it a flux controller?
	if (!esc && (**c == '>' || **c == '<' || **c == '|' || **c = ';'))
	//is it a semicolumn?
	if (!esc && (**c == ';'))
	//is it a 'regular'?
	else

}


//Main function for lexing the input into a list of tokens.
t_tokens		*tokenize(char	*input)
{
	t_tokens	*toks;
	char		*ptr;
	int			esc;

	toks = NULL;
	esc = 0;
	while (*ptr)
	{
		while (ft_isspacer(ptr))
			ptr++;
		if (!esc && *ptr == '\\')
		{
			esc = 1;
			ptr++;
			continue ;
		}
		toks = get_next_token(&ptr, toks, esc);
		esc = 0;
	}
	return (toks);
}
