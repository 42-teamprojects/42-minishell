/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:24:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/08 23:24:55 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell **shell)
{
	int			i;

	i = 0;
	while (i < (*shell)->cmds[0]->argc)
	{
		printf("%s ", (*shell)->cmds[0]->args[i]);
		i++;
	}
	printf("\n");
}
