/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/23 18:27:43 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

size_t		get_tab_size(char **tab)
{
	size_t	size;
	char	**roam;

	if (!tab)
		return (0);
	roam = tab;
	size = 0;
	while (*roam)
	{
		size++;
		roam++;
	}
	return (size);
}

char		**get_env(char **environ)
{
	char	**copy;
	char	**env_ptr;
	char	**cpy_ptr;

	if (!environ)
		return (NULL);
	if (!(copy = malloc(sizeof(copy) * (get_tab_size(environ) + 1))))
		exit(EXIT_FAILURE);
	env_ptr = environ;
	cpy_ptr = copy;
	while (*env_ptr)
	{
		if (!(*cpy_ptr = ft_strdup(*env_ptr)))
			exit(EXIT_FAILURE);
		cpy_ptr++;
		env_ptr++;
	}
	*cpy_ptr = NULL;
	return (copy);
}

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
		//do the expansions
		toks_groups = split_commands(toks);
		curr = toks_groups;
		while (*curr)
		{
			printf("===============\n");
			display_ll(*curr);
			//go into Dispatch:
			//	-split each command groups into execution groups
			//	 as elements of the pipeline.
			//	-split each execution groups in two groups:
			//		- redirections
			//		- command (program and its arguments)
			//	-start the pipeline execution:
			//	 at each stage of the pipeline
			//	 	- pipe the command
			//	 	- do the redirections in order
			//	 	- execute the current command
			curr++;
		}
	}
	return (1);
}

int			main(void)
{
	extern char **environ;
	char		**env;

	if (!(env = get_env(environ)))
		return (-1);
	title();
	prompt_loop();
	return (0);
}
