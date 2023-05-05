/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:18:01 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/05 16:29:11 by yelaissa         ###   ########.fr       */
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

void	ft_exit(t_shell **shell, int idx)
{
	int	exit_value;

	if ((*shell)->cmds[idx]->argc == 0)
		exit((*shell)->status_code);
	if (check_for_int((*shell)->cmds[idx]->args[0]) == -1)
	{
		console(1, "exit", "numeric argument required");
		exit(1 % 256);
	}
	else if ((*shell)->cmds[idx]->argc >= 2)
	{
		console(1, "exit", "too many arguments");
		return ;
	}
	else
	{
		exit_value = ft_atoi((*shell)->cmds[idx]->args[0]);
		exit(exit_value % 256);
	}
}
