/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/19 00:07:57 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_shell **shell)
{
	pid_t	pid;
	int		state;

	pid = fork();
	if (pid == -1)
	{
		console(1, "", strerror(errno));
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve((*shell)->cmds[0]->path, (*shell)->cmds[0]->full_cmd, \
			(*shell)->env) == -1)
		{
			console(1, (*shell)->cmds[0]->path, strerror(errno));
			stop(1, shell);
		}
	}
	else
	{
		waitpid(pid, &state, 0);
		(*shell)->status_code = (int)(state >> 8);
		return (0);
	}
	dup2((*shell)->old_out, STDOUT_FILENO);
	return (0);
}

void	ft_exec_builtin(t_shell **shell)
{
	char	*cmd_name;

	cmd_name = (*shell)->cmds[0]->name;
	if (ft_strchr((*shell)->cmds[0]->name, '/') != NULL)
		cmd_name = remove_slashes((*shell)->cmds[0]->name);
	if (!ft_strcmp(ft_tolowercase(cmd_name), "echo") || \
		!ft_strcmp(ft_tolowercase(cmd_name), "/bin/echo"))
		ft_echo(shell);
	else if (!ft_strcmp(cmd_name, "cd") || \
		!ft_strcmp(cmd_name, "/usr/bin/cd"))
		ft_cd(shell);
	else if (!ft_strcmp(ft_tolowercase(cmd_name), "pwd") || \
		!ft_strcmp(ft_tolowercase(cmd_name), "/bin/pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(ft_tolowercase(cmd_name), "env") || \
		!ft_strcmp(ft_tolowercase(cmd_name), "/usr/bin/env"))
		ft_env(shell);
	else if (!ft_strcmp(cmd_name, "export"))
		ft_export(shell);
	else if (!ft_strcmp(cmd_name, "unset"))
		ft_unset(shell);
}
