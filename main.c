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

/*
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

void	print_cmd(t_data *data)
{
	t_command	*cmd;
	char		**str;

	cmd = data->commands;
	while (cmd)
	{
		if (cmd->str)
			printf("%s\n", cmd->str);
		str = cmd->args;
		while (str)
		{
			printf("%s ", *str);
			str++;
		}
		printf("\n");
		printf("%s : %d\n", cmd->io_data.infile, cmd->io_data.in_fd);
		if (cmd->io_data.heredoc_del)
			printf("%s\n", cmd->io_data.heredoc_del);
		printf("%s : %d\n", cmd->io_data.outfile, cmd->io_data.out_fd);
		cmd = cmd->next;
	}
}*/

void	use_input(t_data *data)
{
	if (!lexer(data))
	{
		data->status = 2;
		return ;
	}
	if (!parser(data))
	{
		data->status = 1;
		return ;
	}
	execution(data);
}

int	minishell_inter(t_data *data)
{
	while (1)
	{
		free_data(data);
		set_signals_interactive();
		data->line = readline("minishell> ");
		if (!data->line)
			exit_shell(data);
		if (!data->line[0] || check_line(data->line))
			continue ;
		set_signals_noninteractive();
		add_history(data->line);
		use_input(data);
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
