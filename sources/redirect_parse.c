/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:25:55 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 16:57:30 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

/*
	printf("---------------\n");
	printf("| l_value is %s\n", redir_toks->l_value);
	printf("| operand is %s\n", redir_toks->operand);
	printf("| r_value is %s\n", redir_toks->r_value);
	printf("---------------\n");
*/
static t_redirect	*extract_redir_values(char *unlexd_redir)
{
	t_redirect	*lexd_redir;
	char		*start;
	char		*end;

	if (!unlexd_redir)
		return (NULL);
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
	return (lexd_redir);
}

static int			apply_redirections(t_redirect *redir_toks)
{

	if (!redir_toks)
		return (0);
	if (!ft_strcmp(redir_toks->operand, ">")
		|| !ft_strcmp(redir_toks->operand, ">>"))
	{
		printf("[%s] its output\n", redir_toks->operand);
		apply_output_redir(redir_toks->operand, redir_toks->l_value,
				redir_toks->r_value);
	}
	else if (!ft_strcmp(redir_toks->operand, "<")
		|| !ft_strcmp(redir_toks->operand, "<<"))
	{
		printf("[%s] its input\n", redir_toks->operand);
		apply_input_redir(redir_toks->operand, redir_toks->l_value,
				redir_toks->r_value);
	}
	return (1);
}

void				redirect(t_tokens *redirections)
{
	t_tokens	*curr;
	t_redirect	*redir_toks;
	
	if (!redirections)
		return ;
	curr = redirections;
	while (curr)
	{
		redir_toks = extract_redir_values(curr->string);
		if (!(apply_redirections(redir_toks)))
		{
			ft_putendl_fd("21sh: redirections error.", 2);
			exit(EXIT_FAILURE);
		}
		curr = curr->next;
	}
	return ;
}
