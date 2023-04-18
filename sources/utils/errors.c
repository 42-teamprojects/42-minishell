/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:57:19 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/18 14:47:35 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop(int err_code, t_shell **shell)
{
	if (err_code == 1)
	{
		(*shell)->exit = 1;
		printf("\n");
	}
	if (err_code)
		(*shell)->exit = err_code;
}

void	console(int status, char *cmd, char *err)
{
	if (status == 0)
		ft_printf_fd(2, BGREEN"→  "CX "minishell: %s: %s\n"CX, cmd, err);
	else
		printf(BRED"→  "CX "minishell: %s: %s\n"CX, cmd, err);
}

void	not_found(char *cmd)
{
	ft_printf_fd(0, BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
		cmd);
}
