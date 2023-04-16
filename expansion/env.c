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

char	*get_var_env(t_data *data, char *var)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	if (var[i] && var[i] == '?')
		return (ft_itoa(data->status));
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	j = 0;
	while (data->env[j])
	{
		if (!ft_strncmp(data->env[j], var, i))
		{
			val = ft_strdup(data->env[j] + i + 1);
			if (!val)
				return (0);
			return (val);
		}
		j++;
	}
	return (ft_strdup(""));
}

static int	get_int_size(int nbr)
{
	int	size;

	size = 0;
	if (!nbr)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

int	get_var_size(t_data *data, char *var)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	size = 0;
	if (var[i] && var[i] == '?')
		return (get_int_size(data->status));
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	j = 0;
	while (data->env[j])
	{
		if (!ft_strncmp(data->env[j], var, i))
		{
			while (*(data->env[j] + i + 1 + size))
				size++;
			return (size);
		}
		j++;
	}
	return (0);
}
