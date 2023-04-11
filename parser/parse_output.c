/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:13:36 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:13:39 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_output(t_command *command)
{
	if (command->io_data.out_fd != -1)
		close(command->io_data.out_fd);
	command->io_data.outfile = 0;
	command->io_data.out_fd = -1;
}

int	parse_append(t_command *command, t_token **token)
{
	if (init_parse_io(command, token, 0))
		return (0);
	if (!rm_quotes(&((*token)->str)))
		return (0);
	command->io_data.outfile = (*token)->str;
	command->io_data.out_fd = open(command->io_data.outfile,
			O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (command->io_data.out_fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (0);
	}
	return (1);
}

int	parse_trunc(t_command *command, t_token **token)
{
	if (init_parse_io(command, token, 0))
		return (0);
	if (!rm_quotes(&((*token)->str)))
		return (0);
	command->io_data.outfile = (*token)->str;
	command->io_data.out_fd = open(command->io_data.outfile,
			O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (command->io_data.out_fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (0);
	}
	return (1);
}
