#include "../includes/21sh.h"

static size_t	get_groups_number(t_tokens *toks)
{
	t_tokens	*curr;
	size_t		n;

	curr = toks;
	n = 1;
	while (curr)
	{
		if (curr->type == SCL && curr->next)
			n++;
		curr = curr->next;
	}
	return (n);
}

static t_tokens	**init_tokens_groups(size_t size)
{
	t_tokens **toks_groups;
	t_tokens **curr;

	if (!(toks_groups = malloc(sizeof(toks_groups) * size + 1)))
		exit(EXIT_FAILURE);
	curr = toks_groups;
	while (size + 1)
	{
		toks_groups[size] = NULL;
		size--;
	}
	return (toks_groups);
}

t_tokens	**split_commands(t_tokens *toks)
{
	t_tokens	**toks_groups;
	t_tokens	*curr_list;
	t_tokens	**curr_group;

	if (!toks)
		return (NULL);
	toks_groups = init_tokens_groups(get_groups_number(toks));
	curr_list = toks;
	curr_group = toks_groups;
	while (curr_list)
	{
		if (curr_list->type != SCL)
		{
			*curr_group = add_token_node
			(*curr_group, curr_list->string, curr_list->type);
		}
		else
			curr_group++;
		curr_list = curr_list->next;
	}
	return (toks_groups);
}