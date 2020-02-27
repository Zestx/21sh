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

static int	open_file(char *r_value)
{
	int fd;

	fd = -1;
	printf("opening [%s]\n", r_value);
	if (access(r_value, F_OK))
	{
		ft_putendl("file does not exist!");
		return (0);
	}
	else if (access(r_value, R_OK))
	{
		perror("access R_OK error: ");
		return (-1);
	}
	fd = open(r_value, O_RDONLY);
		ft_putendl("bad fd.");
	printf("FD: %d", fd);
	if (fd < 0)
	{
		ft_putendl("error: negative fd.\n");
		return (fd);
	}
	return (fd);
}

static int	get_output_fd(char *l_value)
{
	if (!ft_strlen(l_value))
		return (1);
	else if (ft_isdigit(*l_value))
		return (ft_atoi(l_value));
	else
		return (-1);
}

static int	get_input_fd(char *r_value)
{
	if (ft_strlen(r_value) == 0)
	{
		ft_putendl("error: r_value is empty.");
		return (-1);
	}
	else if (ft_isdigit(r_value[1]) && r_value[2] == '\0')
		return (ft_atoi(&(r_value[1])));
	return (open_file(r_value));
}

int		apply_input_redir(char *operand, char *l_value, char *r_value)
{
	int input_fd;

	input_fd = get_input_fd(r_value);
	if (input_fd < 0)
	{
		ft_putendl("input_fd error!");
		return (0);
	}
	if (input_fd > 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		return (0);
	}
	else
	{
		ft_putendl("input_fd is 0");
		return (0);
	}
	return (1);
}
