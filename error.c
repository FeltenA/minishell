/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:11:50 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:11:54 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg, char *token, int quoting)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (quoting)
		ft_putstr_fd(" `", 2);
	else
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(token, 2);
	if (quoting)
		ft_putstr_fd("\'", 2);
	ft_putstr_fd("\n", 2);
}
