

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
		if (ft_strncmp(env[j], var[0], i))
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
		if (ft_strncmp(env[j], var[0], i))
		{
			while (env[j + i + 1 + size])
				size++;
			return (size);
		}
		j++;
	}
	return (0);
}

int	get_new_word_size(char **env, char *str)
{
	int	i;
	int	size;
	int	quotes;

	i = 0;
	size = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		if (str[i] =='\'' || str[i] == '\"')
			quotes = set_quote_status(quotes, str[i]);
		else if (str[i] == '$' && quotes != SQUOTE)
		{
			size += get_var_size(data->env, &str[i]);
			while (str[i] && ft_isalnum(str[i]))
				i++;
			continue ;
		}
		i++;
		size++;
	}
	return (size);
}

int	replace_var(t_data *data, char *str)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	j = 0;
	quotes = DEFAULT;
	while (str[i])
	{
		if (str[i] =='\'' || str[i] == '\"')
			quotes = set_quote_status(quotes, str[i]);
		else if (str[i] == '$' && quotes != SQUOTE)
		{
			while (var[i] && ft_isalnum(var[i]))
				i++;
			size += get_var_size(data->env, &str[i]);
		}
	}
}