/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:39 by afelten           #+#    #+#             */
/*   Updated: 2023/04/12 16:07:41 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	fill_heredoc(int fd, char *del, int quotes, char **env)
{
	char	*line;

	line = readline("heredoc> ");
	while (line && ft_strncmp(del, line, ft_strlen(del)))
	{
		if (replace_var(&line, quotes, env))
		{
			free(line);
			return (0);
		}
		ft_putstr_fd(line, fd);
		free(line);
		line = readline("heredoc> ");
	}
	if (!line)
		ft_putstr_fd("warning: here-document delimited by end-of-file: wanted del", 2);
	else
		free(line);
	return (1);
}

int	create_heredoc(char **env, char	*file, char **del)
{
	int	fd;
	int	quotes;
	int	ret;

	quotes = get_nbr_quotes(*del);
	if (!rm_quotes(del))
		return (0);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (0);
	}
	ret = fill_heredoc(fd, *del, quotes, env);
	close(fd);
	return (ret);
}

int	parse_heredoc(t_command *command, t_token **token, char **env)
{
	if (init_parse_io(command, token, 1))
		return (0);
	command->io_data.infile = get_heredoc_name();
	if (!command->io_data.infile)
		return (0);
	command->io_data.heredoc_del = (*token)->str;
    if (create_heredoc(env, command->io_data.infile,
			&command->io_data.heredoc_del))
		return (0);
	command->io_data.in_fd = open(command->io_data.infile,
			O_RDONLY, 0664);
	if (command->io_data.in_fd < 0)
		return (0);
	return (1);
}