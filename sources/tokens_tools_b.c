/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_tools_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:59:54 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:05:20 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	*add_char(char *str, char c)
{
	char	*new_str;
	char	*new_ptr;
	char	*org_ptr;
	size_t	len;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	if (!(new_str = malloc(len + 2)))
		exit(EXIT_FAILURE);
	new_ptr = new_str;
	org_ptr = str;
	while (org_ptr && *org_ptr)
	{
		*new_ptr = *org_ptr;
		new_ptr++;
		org_ptr++;
	}
	*new_ptr = c;
	new_ptr++;
	*new_ptr = '\0';
	if (str)
		free(str);
	return (new_str);
}

int		ft_issquote(char c)
{
	return (c == '\'');
}

int		ft_isdquote(char c)
{
	return (c == '\"');
}

int		ft_isbquote(char c)
{
	return (c == '\\');
}

void	display_ll(t_tokens *toks)
{
	t_tokens	*ptr;
	int			n;

	if (!toks)
		return ;
	n = 0;
	ptr = toks;
	while (ptr)
	{
		printf("%d. [%s] ", n, ptr->string);
		if (ptr->type == 1)
			printf("REG\n");
		if (ptr->type == 2)
			printf("QOT\n");
		if (ptr->type == 3)
			printf("PIP\n");
		if (ptr->type == 4)
			printf("RED\n");
		if (ptr->type == 5)
			printf("SCL\n");
		ptr = ptr->next;
		n++;
	}
	printf("=================\n");
}
