/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:53:18 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 19:37:15 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int	get_left_fd(char curr_c)
{
	int fd;

	if (curr_c == '>')
		fd = 1;
	else if (curr_c == '<')
		fd = 0;
	else
	{
		fd = (curr_c) - 48;
		curr_c++;
	}
	return (fd);
}

static int	get_right_fd(char *r_value, char *curr_c)
{
	int fd;

	fd = -1;
	if (*curr_c == '>' && *(curr_c + 1 ) == '\0')
		fd = open(r_value, O_WRONLY|O_CREAT, 0666);
	else if (*curr_c == '>' && *(curr_c + 1) == '>')
		fd = open(r_value, O_WRONLY|O_CREAT|O_APPEND, 0666);
	else if (*curr_c == '<' && *(curr_c + 1) == '\0')
		fd = open(r_value, O_RDONLY|O_CREAT, 0666);
	if (fd < 0)
		perror("open error: ");
	return (fd);
}

static void	apply_redirection(t_tokens *pnode)
{
	int	fd_l;
	int	fd_r;
	char	*curr_c;

	if (pnode->next == NULL)
	{
		ft_putendl_fd("redirection error: missing R_VALUE", 2);
		return ;
	}
	curr_c = pnode->string;
	fd_l = get_left_fd(*curr_c);
	if ((fd_r = get_right_fd(pnode->next->string, curr_c)) < 0)
		return ;
	dup2(fd_r, fd_l);
	close(fd_r);
}

void		redirect(t_tokens *pnode)
{
	t_tokens *curr_tok;

	curr_tok = pnode;
	while (curr_tok)
	{
		if (curr_tok->subtype == REDI)
		{
			apply_redirection(curr_tok);
		}
		curr_tok = curr_tok->next;
	}
}
