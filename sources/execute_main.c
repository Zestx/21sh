/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:07:50 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:08:27 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int	err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

static void	execute(char **cmd_list)
{
	execvp(cmd_list[0], cmd_list);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}

static void	execute_pipeline(t_pnode *cmd_list)
{
	int		p[2];
	pid_t	pid;
	t_pnode	*curr;

	if (!cmd_list)
		return ;
	curr = cmd_list;
	while (curr->next)
	{
		if (pipe(p) < 0)
			err_handler("pipe error: ");
		pid = fork();
		if (pid < 0)
			err_handler("fork error: ");
		else if (pid == 0)
		{
			redirect(curr->reds);
			close(p[0]);
			dup2(p[1], 1);
			close(p[1]);
			execute(curr->cmds);
			perror("exec error: ");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			close(p[1]);
			dup2(p[0], 0);
			close(p[0]);
			wait(&pid);
		}
		curr = curr->next;
	}
	execute(curr->cmds);
}

void		execute_main(t_pnode *cmd_list)
{
	pid_t	pid;

	if (!cmd_list)
		return ;
	pid = fork();
	if (pid < 0)
		err_handler("fork error: ");
	else if (pid == 0)
	{
		if (cmd_list->next == NULL)
		{
			redirect(cmd_list->reds);
			execute(cmd_list->cmds);
			perror("exec error: ");
			exit(EXIT_FAILURE);
		}
		else
			execute_pipeline(cmd_list);
	}
	else if (pid > 0)
		wait(&pid);
}
