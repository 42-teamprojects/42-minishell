/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:05 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/24 16:06:25 by htalhaou         ###   ########.fr       */
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

void	redirect_pipe(int i)
{
	if (i > 0)
		dup2((g_shell)->cmds[i - 1]->fd[0], STDIN_FILENO);
	if (i < (g_shell)->cmds_count - 1)
		dup2((g_shell)->cmds[i]->fd[1], STDOUT_FILENO);
}
