/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/05 18:55:49 by qbackaer         ###   ########.fr       */
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

static size_t	count_spec_nodes(t_tokens *toks, int spec)
{
	size_t		count;
	t_tokens	*curr;

	if (!toks)
		return (0);
	curr = toks;
	count = 0;
	while (curr)
	{
		if (curr->type == spec)
			count++;
		curr = curr->next;
	}
	return (count);
}

//should probably be parsed into a special kind of struct/list.
static t_tokens *gather_redir_tokens(t_tokens *group)
{
	t_tokens	*gathered;
	t_tokens	*curr;
	size_t		size;

	if (!group)
		return (NULL);
	size = count_spec_nodes(group, RED);
	if (!(gathered = malloc(sizeof(curr) * size)))
		exit(EXIT_FAILURE);
	gathered = NULL;
	curr = group;
	while (curr)
	{
		if (curr->type == RED)
			gathered = add_token_node(gathered, curr->string, RED);
		curr = curr->next;
	}
	return (gathered);
}

static t_tokens *gather_cmds_tokens(t_tokens *group)
{
	t_tokens	*gathered;
	t_tokens	*curr;
	size_t		size;

	if (!group)
		return (NULL);
	size = count_spec_nodes(group, REG) + count_spec_nodes(group, QOT);
	if (!(gathered = malloc(sizeof(curr) * size)))
		exit(EXIT_FAILURE);
	gathered = NULL;
	curr = group;
	while (curr)
	{
		if (curr->type == REG || curr->type == QOT)
			gathered = add_token_node(gathered, curr->string, REG);
		curr = curr->next;
	}
	return (gathered);
}

static int	dispatch(t_tokens *cmd_group)
{
	t_tokens	**pipeline;
	t_tokens	**curr;
	t_tokens	*redirs;
	t_tokens	*args;

	pipeline = split_commands(cmd_group, PIP);
	curr = pipeline;
	while (*curr)
	{
			redirs = gather_redir_tokens(*curr);
			args = gather_cmds_tokens(*curr);
			printf("ARGS: \n");
			display_ll(args);
			printf("REDS: \n");
			display_ll(redirs);
			//	-start the pipeline execution:
			//	 at each stage of the pipeline
			//	 	- pipe the command
			//	 	- do the redirections in order
			//	 	- execute the current command
			curr++;
	}
	return (1);
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
		toks_groups = split_commands(toks, SCL);
		curr = toks_groups;
		while (*curr)
		{
			dispatch(*curr);
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
