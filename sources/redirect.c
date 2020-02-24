/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:25:55 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/19 19:31:55 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

//extract l_value, r_value and operand and
//put it in a new t_redirect structure.	
static t_redirect	*extract_redir_values(char *unlexd_redir)
{
	t_redirect	*lexd_redir;
	char		*start;
	char		*end;

	if (!(lexd_redir = malloc(sizeof(t_redirect))))
		exit(EXIT_FAILURE);
	start = unlexd_redir;
	end = unlexd_redir;
	while (*end != '>' && *end != '<')
		end++;
	if (!(lexd_redir->l_value = strndup(start, end - start)))
		exit(EXIT_FAILURE);
	start = end;
	while (*end == '>' || *end == '<')
		end++;
	if (!(lexd_redir->operand = strndup(start, end - start)))
		exit(EXIT_FAILURE);
	if (!(lexd_redir->r_value = strdup(end)))
		exit(EXIT_FAILURE);
	return (NULL);
}

static t_redirect	*get_redir_tokens(t_tokens *unlexd_redir)
{
	t_redirect	*lexd_redir;

	if (!unlexd_redir)
		return (NULL);
	lexd_redir = extract_redir_values(unlexd_redir->string);

	return (lexd_redir);
}
/*
static int		apply_redirections(t_redirect *redir_toks)	
{
	//parse the redirection tokens to know the 'source' fd
	//and the 'destination' fd, then pipe them using dup2().
}
*/
void			redirect(t_tokens *redirections)
{
	t_tokens	*curr;
	t_redirect	*redir_toks;

	if (!redirections)
		return;
	curr = redirections;
	while (curr)
	{
		redir_toks = get_redir_tokens(curr);
		/*if (!(apply_redirections(redir_toks)))
		{
			ft_putendl_fd("21sh: redirections error.");
			exit(EXIT_FAILURE);
		};*/
		curr = curr->next;
	}
	return ;
}
