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

int	add_arg_command(t_command *command, t_token *token)
{
	if (!command->args)
	{
		command->args = malloc(sizeof(char *));
		if (!command->args)
			return (0);
		command->args[0] = 0;
	}
	command->args = add_str_arr(command->args, token->str);
	if (!command->args)
		return (0);
	return (1);
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
		command->str = (*token)->str;
	else
		return (add_arg_command(command, *token));
	return (1);
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
