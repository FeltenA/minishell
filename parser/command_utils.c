/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:35:44 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 17:35:46 by afelten          ###   ########.fr       */
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