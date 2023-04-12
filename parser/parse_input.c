/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:13:27 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:13:30 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input(t_command *command)
{
	if (command->io_data.in_fd != -1)
		close(command->io_data.in_fd);
	if (command->io_data.heredoc_del)
	{
		unlink(command->io_data.infile);
		free(command->io_data.heredoc_del);
		command->io_data.heredoc_del = 0;
	}
	command->io_data.infile = 0;
	command->io_data.in_fd = -1;
}

int	init_parse_io(t_command *command, t_token **token, int input)
{
	*token = (*token)->next;
	if (!ft_strlen((*token)->str))
	{
		ft_putstr_fd("ambiguous redirect", 2);
		return (0);
	}
	if (input)
		free_input(command);
	else
		free_output(command);
	return (1);
}

char	*get_heredoc_name(void)
{
	static int	i;
	char		*str;
	char		*str2;

	str2 = ft_itoa(i);
	if (!str2)
		return (0);
	str = ft_strjoin(".heredoc", str2);
	free(str2);
	return (str);
}

int	create_heredoc(char	*file, char **del)
{
	int	fd;
	int	quotes;

	quotes = get_nbr_quotes(*del);
	if (!rm_quotes(del))
		return (0);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

int	parse_heredoc(t_command *command, t_token **token)
{
	if (init_parse_io(command, token, 1))
		return (0);
	command->io_data.infile = get_heredoc_name();
	if (!command->io_data.infile)
		return (0);
	command->io_data.heredoc_del = (*token)->str;
}

int	parse_input(t_command *command, t_token **token)
{
	if (init_parse_io(command, token, 1))
		return (0);
	if (!rm_quotes(&((*token)->str)))
		return (0);
	command->io_data.infile = (*token)->str;
	command->io_data.in_fd = open(command->io_data.infile,
			O_RDONLY, 0664);
	if (command->io_data.in_fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (0);
	}
	return (1);
}
