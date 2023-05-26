/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:20:49 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 17:27:16 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *file)
{
	int	fd;

	if (g_shell->openheredoc == 0)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (console(1, file, strerror(errno)), 1);
	(g_shell)->fd.old_in = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirect_output(char *file, t_token_type type)
{
	int	fd;

	if (type == RD_OUT)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (console(1, file, strerror(errno)), 1);
	(g_shell)->fd.old_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	dupping(void)
{
	dup2((g_shell)->fd.orig_stdout, STDOUT_FILENO);
	dup2((g_shell)->fd.orig_stdin, STDIN_FILENO);
}

int	handle_redirection(t_rd *rd)
{
	(g_shell)->fd.orig_stdout = dup(STDOUT_FILENO);
	(g_shell)->fd.orig_stdin = dup(STDIN_FILENO);
	if (!rd)
		return (1);
	while (rd)
	{
		if (rd->type == RD_OUT || rd->type == RD_AOUT)
		{
			if (redirect_output(rd->file, rd->type))
				return (dupping(), 1);
		}
		else if (rd->type == RD_IN || rd->type == HEREDOC)
		{
			if (redirect_input(rd->file))
				return (dupping(), 1);
		}
		rd = rd->next;
	}
	return (0);
}
