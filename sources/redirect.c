/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:53:18 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 16:54:10 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int	get_file_fd(char *path, char *curr_c)
{
	int fd;

	fd = -1;
	if (*curr_c == '>' && *(curr_c + 1 ) == '\0')
		fd = open(path, O_WRONLY|O_CREAT, 0666);
	else if (*curr_c == '>' && *(curr_c + 1) == '>')
		fd = open(path, O_WRONLY|O_CREAT|O_APPEND, 0666);
	else if (*curr_c == '<' && *(curr_c + 1) == '\0')
		fd = open(path, O_RDONLY|O_CREAT, 0666);
	if (fd < 0)
		perror("open error: ");
	return (fd);
}

void	apply_redirection(t_tokens *pnode)
{
	int	fd_l;
	int	fd_r;
	char	*curr_c;

	curr_c = pnode->string;
	if (ft_isdigit(*curr_c))
	{
		fd_l = (*curr_c) - 48;
		curr_c++;
	}
	else if (*curr_c == '>')
		fd_l = 1;
	else if (*curr_c == '<')
		fd_l = 0;
	else
		ft_putendl_fd("redirection format error.", 2);
	if ((fd_r = get_file_fd(pnode->next->string, curr_c)) < 0)
		return ;
	dup2(fd_r, fd_l);
	close(fd_r);
}

void	redirect(t_tokens *pnode)
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
