/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:35:29 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/15 16:00:38 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(t_rd *rd)
{
	int	fd;

	fd = open(rd->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		check_file(rd);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_input(t_rd *rd)
{
	int	fd;

	fd = open(rd->file, O_RDONLY);
	if (fd < 0)
	{
		check_file(rd);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	check_file(t_rd *rd)
{
	if (access(rd->file, F_OK) == -1)
	{
		console(1, rd->file, ": No such file or directory");
		return (1);
	}
	else if (access(rd->file, R_OK) == -1)
	{
		console(1, rd->file, ": Permission denied");
		return (1);
	}
	else if (access(rd->file, X_OK) == 0)
	{
		console(1, rd->file, ": Is a directory");
		return (1);
	}
	return (0);
}

int	append(t_rd *rd)
{
	int fd;

	fd = open(rd->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		check_file(rd);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirection(t_rd *rd)
{
	while (rd)
	{
		if (rd->type == RD_OUT)
		{
			if (redirect_output(rd))
				return (1);
		}
		else if (rd->type == RD_IN)
		{
			if (redirect_input(rd))
				return (1);
		}
		else if (rd->type == RD_AOUT)
		{
			if (append(rd))
				return (1);
		}
		rd = rd->next;
	}
	return (0);
}
