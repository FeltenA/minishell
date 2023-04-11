/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:14:03 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:14:06 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (0);
	command->str = 0;
	command->args = 0;
	command->pipe = 0;
	command->prev = 0;
	command->next = 0;
	command->io_data.infile = 0;
	command->io_data.outfile = 0;
	command->io_data.heredoc_del = 0;
	command->io_data.in_fd = -1;
	command->io_data.out_fd = -1;
	return (command);
}

void	add_command(t_command **commands, t_command *new)
{
	t_command	*list;

	list = *commands;
	while (list && list->next)
		list = list->next;
	if (!list)
		*commands = new;
	else
	{
		list->next = new;
		new->prev = list;
	}
}

int	fill_command(t_command *command, t_token **token)
{
	if ((*token)->type == TRUNC)
		return (parse_trunc(command, token));
	else if ((*token)->type == APPEND)
		return (parse_append(command, token));
	else if ((*token)->type == INPUT)
		return (parse_input(command, token));
	else if ((*token)->type == HEREDOC)
		return (parse_heredoc(command, token));
	else if (!command->str)
		return (parse_command(command, *token));
	else
		return (add_arg_command(command, *token));
}

int	create_command(t_data *data, t_token **tokens)
{
	t_command	*new;

	new = init_command();
	if (!new)
		return (0);
	add_command(&data->commands, new);
	while (*tokens && (*tokens)->type != PIPE && (*tokens)->type != END)
	{
		if (!fill_command(new, tokens))
			return (0);
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	parser(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		if (create_command(data, &token))
			return (0);
		if (token)
			token = token->next;
	}
	return (1);
}
