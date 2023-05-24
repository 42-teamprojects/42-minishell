/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:24:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/24 16:24:59 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_option(char *opt)
{
	int	i;

	i = 0;
	opt = opt + 1;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_for_option(char **args, int *flag)
{
	int	i;

	if (*args[0] != '-')
		return (0);
	i = 0;
	while (args[i])
	{
		if (*args[i] == '-' && !is_valid_option(args[i]))
			return (i);
		else if (*args[i] == '-' && is_valid_option(args[i]))
			*flag = 1;
		i++;
		if (*args[i] != '-')
			break ;
	}
	return (i);
}

int	ft_echo(int idx)
{
	int	i;
	int	flag;

	flag = 0;
	if (!(g_shell)->cmds[idx]->args)
	{
		printf("\n");
		return (0);
	}
	i = check_for_option((g_shell)->cmds[idx]->args, &flag);
	while (i < (g_shell)->cmds[idx]->argc)
	{
		if (i != (g_shell)->cmds[idx]->argc - 1)
			printf("%s ", (g_shell)->cmds[idx]->args[i]);
		else
			printf("%s", (g_shell)->cmds[idx]->args[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
