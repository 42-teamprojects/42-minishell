/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:57:19 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/25 18:46:16 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop(int err_code)
{
	if (err_code == 1)
	{
		(g_shell)->exit = 1;
		printf("\n");
	}
	if (err_code)
		(g_shell)->exit = err_code;
}

void	console(int status, char *cmd, char *err)
{
	if (status == 1)
		ft_printf_fd(2, "minishell: %s: %s\n", cmd, err);
	else
		ft_printf_fd(1, "minishell: %s: %s\n", cmd, err);
}
