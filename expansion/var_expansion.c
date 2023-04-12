/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:14:20 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:14:24 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_word_size(char **env, char *str, int heredoc)
{
	int	i;
	int	size;
	int	quotes;

	i = 0;
	size = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quotes = set_quote_status(quotes, str[i]);
		else if (str[i] == '$' && ft_isalnum(str[i + 1])
			&& (quotes != SQUOTE || heredoc == DEFAULT))
		{
			i++;
			size += get_var_size(env, &str[i]);
			while (str[i] && ft_isalnum(str[i]))
				i++;
			continue ;
		}
		i++;
		size++;
	}
	return (size);
}

int	check_var(char *str, int heredoc)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quotes = set_quote_status(quotes, str[i]);
		else if (str[i] == '$' && ft_isalnum(str[i + 1])
			&& (quotes != SQUOTE || heredoc == DEFAULT))
			return (1);
		i++;
	}
	return (0);
}

int	copy_var_env(char *str, char *var, int *i)
{
	int	j;

	j = 0;
	if (!var)
		return (0);
	while (var[j])
	{
		str[*i] = var[j];
		*i += 1;
		j++;
	}
	free(var);
	return (1);
}

int	fill_newstr(char *newstr, char *str, char **env, int heredoc)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	j = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quotes = set_quote_status(quotes, str[i]);
		else if (str[i] == '$' && ft_isalnum(str[i + 1])
			&& (quotes != SQUOTE || heredoc == DEFAULT))
		{
			if (!copy_var_env(newstr, get_var_env(env, &str[i + 1]), &j))
				return (0);
			while (str[i] && ft_isalnum(str[i]))
				i++;
		}
		newstr[j] = str[i];
		i++;
		j++;
	}
	newstr[j] = 0;
	return (1);
}

int	replace_var(char **str, int heredoc, char **env)
{
	char	*newstr;

	if (heredoc > DEFAULT || !check_var(str, heredoc))
		return (1);
	newstr = malloc((get_new_word_size(env, *str, heredoc) + 1)
			* sizeof(char));
	if (!newstr)
		return (0);
	if (!fill_newstr(newstr, *str, env, heredoc))
	{
		free(newstr);
		return (0);
	}
	free(*str);
	*str = newstr;
	return (1);
}
