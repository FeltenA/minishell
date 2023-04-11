/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:43:52 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:43:56 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_env(char **env, char *var)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (var[i] && ft_isalnum(var[i]))
		i++;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], var, i))
		{
			var = ft_strdup(env[j] + i + 1);
			if (!var)
				return (0);
			return (var);
		}
		j++;
	}
	return (0);
}

int	get_var_size(char **env, char *var)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	while (var[i] && ft_isalnum(var[i]))
		i++;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], var, i))
		{
			while (env[j] + i + 1 + size)
				size++;
			return (size);
		}
		j++;
	}
	return (0);
}
