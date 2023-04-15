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

int	rediterct_output(t_shell **shell)
{
	int	fd;
	int	i;

	i = 0;
	fd = open((*shell)->cmds[0]->redir->output,
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		check_file((*shell)->cmds[0]->redir->output);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_input(t_shell **shell)
{
	int	fd;

	fd = open((*shell)->cmds[0]->redir->input, O_RDONLY);
	if (fd < 0)
	{
		check_file((*shell)->cmds[0]->redir->input);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	check_file(char *filename)
{
	if (access(filename, F_OK) == -1)
	{
		console(1, filename, ": No such file or directory");
		return (1);
	}
	else if (access(filename, R_OK) == -1)
	{
		console(1, filename, ": Permission denied");
		return (1);
	}
	else if (access(filename, X_OK) == 0)
	{
		console(1, filename, ": Is a directory");
		return (1);
	}
	return (0);
}
