/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:36:09 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:00:31 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int	is_blank_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

int	is_operator(char *c)
{ 
	if (*c == '|' || *c == ';' || *c == '<' || *c == '>')
		return (1);
	if (ft_isdigit(*c) && (*c == '<' || *c == '>'))
		return (1);
	return (0);
}

void	update_quoted_state(int esc, int *quoted, char **curr_c)
{
	int	tmp;

	tmp = *quoted;

	if (!esc && !(*quoted) && **curr_c == '\'')
		*quoted = S_QUOTE;
	else if (!esc && !(*quoted) && **curr_c == '\"')
		*quoted = D_QUOTE;
	else if (*quoted == S_QUOTE && **curr_c == '\'')
		*quoted = 0;
	else if (!esc && *quoted == D_QUOTE && **curr_c == '\"')
		*quoted = 0;
	if (tmp != *quoted)
		(*curr_c)++;
}

void	update_escape_state(int *esc, int quoted, char **curr_c)
{
		if (*esc == 0  && **curr_c == '\\' && quoted != S_QUOTE)
		{
			*esc = 1;
			(*curr_c)++;
		}
}

char	*ctos(char c)
{
	char *str;

	if (!(str = malloc(2)))
		exit(EXIT_FAILURE);
	str[0] = c;
	str[1] = '\0';

	return (str);
}

t_tokens *last_node(t_tokens *head)
{
	t_tokens *curr;

	if (!head)
		return (NULL);
	curr = head;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

char	*add_char_to_token(char *org_str, char c)
{
	char	*new_str;
	char	*org_ptr;
	char	*new_ptr;

	if (!(new_str = malloc(ft_strlen(org_str) + 2)))
		exit(EXIT_FAILURE);
	org_ptr = org_str;
	new_ptr = new_str;
	while (*org_ptr != '\0')
		*(new_ptr++) = *(org_ptr++);
	*(new_ptr++) = c;
	*new_ptr = '\0';
	return (new_str);
}

int	is_part_operator(char *curr_c, int op)
{
	if (op == 1 && ft_isdigit(*(curr_c - 1)) 
			&& (*curr_c == '<' || *curr_c == '>'))
		return (1);
	if ((op == 1 || op == 2) && (*(curr_c - 1) == '<' || *(curr_c - 1) == '>') 
			&& (*(curr_c - 1) == *curr_c || *curr_c == '&'))
		return (1);
	if (op > 2 && (*curr_c == '<' || *curr_c == '>'))
		return (-1);
	else
		return (0);
}

t_tokens	*get_tokens(char *input)
{
	int		esc;
	int		quoted;
	int		operator;
	t_tokens	*toks;
	t_tokens	*curr_tok;
	char		*curr_c;

	curr_c = input;
	operator = 0;
	while (1)
	{
		//01
		if (*curr_c == '\0')
			return (toks);
		if (!esc && !quoted && operator && curr_c > input)
		{
			//02
			if (is_part_operator(curr_c, operator) == 1)
			{
				add_char_to_token(curr_tok->string, *curr_c);
				operator++;
			}
			//03
			else if (is_part_operator(curr_c, operator) == 0)
			{
				operator = 0;
			}
			else if (is_part_operator(curr_c, operator) == -1)
			{
				ft_putendl_fd("21sh: error: syntax error", 2);
				return (NULL);
			}
		}
		//04
		update_quoted_state(esc, &quoted, &curr_c);
		update_escape_state(&esc, quoted, &curr_c);
		//06
		if (!esc && !quoted && is_operator(curr_c) && !operator)
		{
			toks = add_token_node(toks, ctos(*curr_c), OPER);
			curr_tok = last_node(toks);
			operator = 1;
		}
		//07
		if (!esc && !quoted && is_blank_char(*curr_c))
		{
			while (is_blank_char(*curr_c))
				curr_c++;
		}
		//10
		else
		{
			toks = add_token_node(toks, ctos(*curr_c), WORD);
			curr_tok = last_node(toks);
		}
		//--
		curr_c++;
	}
	return (toks);
}
