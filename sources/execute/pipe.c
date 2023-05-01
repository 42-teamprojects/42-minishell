/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:05 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/01 20:11:18 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_shell **shell)
{
	int	i;

	i = 0;
	while (i < (*shell)->cmds_count - 1)
	{
		if (pipe((*shell)->cmds[i]->fd))
			return (1);
		i++;
	}
	return (0);
}

void	close_pipes(t_shell **shell)
{
	int	j;

	j = 0;
	while (j < (*shell)->cmds_count - 1)
	{
		close((*shell)->cmds[j]->fd[0]);
		close((*shell)->cmds[j]->fd[1]);
		j++;
	}
}
