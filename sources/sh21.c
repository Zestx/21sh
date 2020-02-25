/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 16:38:50 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"



//this function split each command groups into "pipeline nodes" then separate
//each nodes into a group of command+args and a group of redirections.
static int	dispatch(t_tokens *cmd_group)
{
	t_pnode		*pipeline_full;
	t_tokens	**pipeline_cmds;
	t_tokens	**curr;
	t_tokens	*redirs;
	char		**args;

	pipeline_cmds = split_commands(cmd_group, PIP);
	free_token_list(cmd_group);
	curr = pipeline_cmds;
	pipeline_full = NULL;
	while (*curr)
	{
			redirs = gather_redir_tokens(*curr);
			args = gather_cmds_tokens(*curr);
			pipeline_full = add_pnode(pipeline_full, args, redirs);
			curr++;
	}
	execute_main(pipeline_full);
	free_pnode_list(pipeline_full);
	return (1);
}

//get user input, split it into command groups (separated by semicolumns)
//and send each groups to dispatch().
static int	prompt_loop(void)
{
	char		*cmds;
	t_tokens	*toks;
	t_tokens	**toks_groups;
	t_tokens	**curr;

	while (1)
	{
		prompt();
		if (!(cmds = get_input()))
			continue ;
		toks = tokenize(cmds);
		free(cmds);
		display_ll(toks);
		//do the expansions
		toks_groups = split_commands(toks, SCL);
		free_token_list(toks);
		curr = toks_groups;
		while (*curr)
		{
			dispatch(*curr);
			*curr = NULL;
			curr++;
		}
		//free(toks_groups);
	}
	return (1);
}

int			main(void)
{
	title();
	prompt_loop();
	return (0);
}
