/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:36:09 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 18:41:07 by qbackaer         ###   ########.fr       */
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
	if (ft_isdigit(*c) && (*(c + 1) == '<' || *(c + 1) == '>'))
		return (1);
	return (0);
}

int	update_quoted_state(int esc, int *quoted, char curr_c)
{
	int	tmp;
	int	ret;

	tmp = *quoted;
	ret = 1;
	if (esc != 1 && !(*quoted) && curr_c == '\'')
		*quoted = S_QUOTE;
	else if (esc != 1 && !(*quoted) && curr_c == '\"')
	{
		printf("DQUOTE\n");
		*quoted = D_QUOTE;
	}
	else if (*quoted == S_QUOTE && curr_c == '\'')
		*quoted = 0;
	else if (esc != 1 && *quoted == D_QUOTE && curr_c == '\"')
		*quoted = 0;
	else
		ret = 0;
	return (ret);
}

int	update_escape_state(int *esc, int quoted, char curr_c)
{
		if (*esc != 1 && curr_c == '\\' && quoted != S_QUOTE)
		{
			*esc = 1;
			return (1);
		}
		else if (*esc == 1)
			*esc += 1;
		else
			*esc = 0;
		return (0);
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

void	add_char_to_token(t_tokens *tok, char c)
{
	char	*new_str;
	char	*org_ptr;
	char	*new_ptr;

	if (!(new_str = malloc(ft_strlen(tok->string) + 2)))
		exit(EXIT_FAILURE);
	org_ptr = tok->string;
	new_ptr = new_str;
	while (*org_ptr != '\0')
		*(new_ptr++) = *(org_ptr++);
	*(new_ptr++) = c;
	*new_ptr = '\0';
	free(tok->string);
	tok->string = new_str;
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

void get_operator(char **curr_c, t_tokens *toks)
{
	char		*curr;
	t_tokens	*working_tok;

	toks = add_token_node(toks, **curr_c, OPER, 0);
	working_tok = last_node(toks);
	curr = *curr_c;
	curr++;
	while (is_part_operator(curr, curr - *curr_c))
	{
		add_char_to_token(working_tok, *curr);
		curr++;
	}
	*curr_c = curr - 1;
}

int			update_inhibitors(int *esc, int *quoted, char curr_c)
{
	if (update_quoted_state(*esc, quoted, curr_c))
		return (1);
	else if (update_escape_state(esc, *quoted, curr_c))
		return (1);
	else
		return (0);
}

t_tokens	*get_next_token(char *curr_c)
{
	int		esc = 0;
	int		quoted = 0;
	int		word = 0;
	t_tokens	*toks = NULL;

	while (*curr_c)
	{
		if (update_inhibitors(&esc, &quoted, *curr_c))
			;
		else if (!esc  && !quoted && is_operator(curr_c))
		{
			word = 0;
			get_operator(&curr_c, toks);
		}
		else if (!esc  && !quoted && is_blank_char(*curr_c))
			word = 0;
		else if (word)
			add_char_to_token(last_node(toks), *curr_c);
		else
		{
			word = 1;
			toks = add_token_node(toks, *curr_c, WORD, 0);
		}
		curr_c++;
	}
	return (toks);
}
