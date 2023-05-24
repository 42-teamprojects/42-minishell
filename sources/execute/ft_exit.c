/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:18:01 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/24 16:25:58 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

int	check_for_int(char *arg)
{
	int	i;

	if (!arg)
		return (-1);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (-1);
		i++;
	}
	return (1);
}

int	ft_exit(int idx)
{
	int	exit_value;

	if ((g_shell)->cmds[idx]->argc == 0)
		exit((g_shell)->status_code);
	if (check_for_int((g_shell)->cmds[idx]->args[0]) == -1)
	{
		(g_shell)->cmds[idx]->args[0] = ft_concat(2, "exit: ", \
			(g_shell)->cmds[idx]->args[0]);
		console(1, (g_shell)->cmds[idx]->args[0], "numeric argument required");
		exit(255);
	}
	else if ((g_shell)->cmds[idx]->argc >= 2)
	{
		console(1, "exit", "too many arguments");
		(g_shell)->status_code = 1;
		return (1);
	}
	else
	{
		exit_value = ft_atoi((g_shell)->cmds[idx]->args[0]);
		exit(exit_value % 256);
	}
	return (0);
}
