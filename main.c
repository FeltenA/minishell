/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:13:10 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:13:14 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c);

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	copy_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (0);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (0);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, char **env)
{
	data->env = 0;
	if (!copy_env(data, env))
	{
		free_str_array(data->env);
		ft_putstr_fd("minishell: Environment initialisation unsuccessful", 2);
		return (0);
	}
	data->line = 0;
	data->status = 0;
	data->tokens = 0;
	data->commands = 0;
	return (1);
}

void	print_tokens(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		printf("%s : %d\n", token->str, token->type);
		token = token->next;
	}
}

int	minishell_inter(t_data *data)
{
	char	*line;

	while (1)
	{
		free_data(data);
		line = readline("minishell> ");
		if (!line || !line[0] || check_line(line))
			continue ;
		data->line = line;
		add_history(line);
		if (!lexer(data))
		{
			data->status = 2;
			continue ;
		}
		print_tokens(data);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (!init_data(&data, env))
		return (1);
	minishell_inter(&data);
	return (0);
}
