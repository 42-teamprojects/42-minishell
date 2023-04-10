/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:24:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/10 22:26:50 by htalhaou         ###   ########.fr       */
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

void	ft_echo(t_shell **shell)
{
	int	i;
	int	flag;

	flag = 0;
	if (!(*shell)->cmds[0]->args[0])
	{
		printf("\n");
		return ;
	}
	i = check_for_option((*shell)->cmds[0]->args, &flag);
	while (i < (*shell)->cmds[0]->argc)
	{
		printf("%s ", (*shell)->cmds[0]->args[i]);
		i++;
	}
	if (!flag)
		printf("\n");
}
