/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:32:36 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/21 19:41:21 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	*get_env_var(char **env, char *var_name)
{
	char	*var_content;
	char	**roam;
	size_t	var_len;

	if (!env || !*env || !var_name)
		return (NULL);
	var_len = 0;
	var_len = ft_strlen(var_name);
	roam = env;
	while (*roam)
	{
		if (!ft_strncmp(*roam, var_name, var_len))
		{
			if (!(var_content = ft_strdup(*roam + var_len + 1)))
				exit(EXIT_FAILURE);
			return (var_content);
		}
		roam++;
	}
	return (NULL);
}
