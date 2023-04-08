/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/08 17:34:24 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_exec(t_shell **shell)
{
	pid_t	pid;
	int		state;

	pid = fork();
	if (pid == -1)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve((*shell)->path, (*shell)->full_cmd, \
			(*shell)->env) == -1)
		{
			printf("%s\n", strerror(errno));
			throw_err(0, shell);
		}
	}
	else
	{
		waitpid(pid, &state, 0);
		return (0);
	}
	return (0);
}

void	ft_exec_builtin(t_shell **shell)
{
	char	*cmd_name;

	cmd_name = (*shell)->cmds[0]->name;
	if (!ft_strcmp(cmd_name, "echo") || \
		!ft_strcmp(cmd_name, "/bin/echo"))
		ft_echo(shell);
	else if (!ft_strcmp(cmd_name, "cd") || \
		!ft_strcmp(cmd_name, "/usr/bin/cd"))
		ft_cd(shell);
	else if (!ft_strcmp(cmd_name, "pwd") || \
		!ft_strcmp(cmd_name, "/bin/pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(cmd_name, "env") || \
		!ft_strcmp(cmd_name, "/usr/bin/env"))
		ft_env(shell);
	else if (!ft_strcmp(cmd_name, "export"))
		ft_export(shell);
	else if (!ft_strcmp(cmd_name, "unset"))
		ft_unset(shell);
}
