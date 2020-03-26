/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 19:01:59 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int	dispatch(t_tokens *cmd_group, t_pwd *pwd, char ***env)
{
	t_tokens	**toks_pseq;

	toks_pseq = split_tokens(cmd_group, PIPE);
	execute_pseq(toks_pseq, pwd, env);
	return (1);
}

static int	prompt_loop(char ***env, t_pwd *pwd)
{
	char		*cmds;
	t_tokens	*toks_all;
	t_tokens	**toks_grp;
	t_tokens	**curr_grp;

	while (1)
	{
		prompt();
		if (!(cmds = get_input()))
			continue ;
		toks_all = lexer(cmds, *env);
		display_ll(toks_all);
		toks_grp = split_tokens(toks_all, SMCL);
		curr_grp = toks_grp;
		while (*curr_grp)
		{
			dispatch(*curr_grp, pwd, env);
			curr_grp++;
		}
	}
	return (1);
}

int			main(void)
{
	extern char	**environ;
	char		**env;
	t_pwd		pwd;

	if (!init_pwd(&pwd))
		exit(EXIT_FAILURE);
	if (!(env = get_env(environ)))
		return (-1);
	title();
	prompt_loop(&env, &pwd);
	return (0);
}
