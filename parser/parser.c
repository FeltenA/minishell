

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
	t_commands	*list;

	list = *commands;
	while (list && list->next)
		list = list->next;
	if (!list)
		*commands = new;
	else
	{
		list->next = new;
		new->prev = list:
	}
}

int	fill_command(t_command *command, t_token **token)
{
	if ((*token)->type == TRUNC)
		return (parse_trunc(new, token));
	else if ((*token)->type == APPEND)
		return (parse_append(new, token));
	else if ((*token)->type == INPUT)
		return (parse_input(new, token));
	else if ((*token)->type == HEREDOC)
		return (parse_heredoc(new, token));
	else if (!str)
		return (parse_command(new, *token));
	else
		return (add_arg_command(new, *token));
}

int	create_command(t_data *data, t_token **tokens)
{
	t_command	*new;

	new = init_command();
	if (!new)
		return (0);
	add_command(&data->commands, new);
	while (*token && (*token)->type != PIPE && (*token)->type != END)
	{
		if (!fill_command(new, token))
			return (0);
		*token = (*token)->next;
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