/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/30 13:15:33 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_exec(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(shell->path, shell->cmd.full_cmd, shell->env) == -1)
		{
			printf("%s\n", strerror(errno));
			throw_err(0, shell);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		return (0);
	}
	return (0);
}

void	ft_exec_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd.name, "echo"))
		ft_echo(shell);
	else if (!ft_strcmp(shell->cmd.name, "cd"))
		ft_cd(shell);
	else if (!ft_strcmp(shell->cmd.name, "pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(shell->cmd.name, "env"))
		ft_env(shell);
	else if (!ft_strcmp(shell->cmd.name, "export"))
		ft_export(shell);
	// else if (!ft_strcmp(shell->cmd.name, "unset"))
	// 	ft_unset(shell);
	// (void) shell;
	// printf("to be implemented\n");
}
