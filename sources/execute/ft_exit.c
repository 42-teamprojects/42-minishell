/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:18:01 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/04 15:35:15 by htalhaou         ###   ########.fr       */
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

	if (check_for_int((*shell)->cmds[idx]->args[0]) == -1)
	{
		ft_printf("exit\nnumeric argument required\n");
		exit(1 % 256);
	}
	else if ((*shell)->cmds[idx]->argc > 2)
	{
		ft_printf("exit\ntoo many arguments\n");
		return ;
	}
	else
	{
		exit_value = ft_atoi((*shell)->cmds[idx]->args[0]);
		exit(exit_value % 256);
	}
}
