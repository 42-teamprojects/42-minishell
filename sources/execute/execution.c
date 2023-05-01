/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/01 18:31:39 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_shell **shell)
{
	pid_t	pid;
	int		i;
	int		j;
	int		state;

	i = 0;
	while (i < (*shell)->cmds_count)
	{
		if (create_pipe((*shell)->cmds[i]))
		{
			printf("Error");
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < (*shell)->cmds_count)
	{
		pid = fork();
		if (pid == -1)
		{
			console(1, "", strerror(errno));
			return (-1);
		}
		else if (pid == 0)
		{
			if (i > 0)
				dup2((*shell)->cmds[i - 1]->fd[0], STDIN_FILENO);
			if (i < (*shell)->cmds_count - 1)
				dup2((*shell)->cmds[i]->fd[1], STDOUT_FILENO);
			j = 0;
			while (j < (*shell)->cmds_count)
			{
				close((*shell)->cmds[j]->fd[0]);
				close((*shell)->cmds[j]->fd[1]);
				j++;
			}
			if (execve((*shell)->cmds[i]->path, (*shell)->cmds[i]->full_cmd,
					(*shell)->env) == -1)
			{
				console(1, (*shell)->cmds[i]->path, strerror(errno));
				stop(1, shell);
			}
			exit(1);
		}
		waitpid(pid, &state, 0);
		close((*shell)->cmds[i]->fd[1]);
		i++;
	}
	i = 0;
	while (i < (*shell)->cmds_count)
	{
		close((*shell)->cmds[i]->fd[0]);
		close((*shell)->cmds[i]->fd[1]);
		i++;
	}
	// (*shell)->status_code = WEXITSTATUS(state);
	return (0);
}

void	ft_exec_builtin(t_shell **shell)
{
	char	*cmd_name;
	char	*low;

	cmd_name = (*shell)->cmds[0]->name;
	low = ft_tolowercase(cmd_name);
	if (ft_strchr(cmd_name, '/') != NULL)
		cmd_name = remove_slashes(cmd_name);
	if (!ft_strcmp(low, "echo") || \
		!ft_strcmp(low, "/bin/echo"))
		ft_echo(shell);
	else if (!ft_strcmp(cmd_name, "cd") || \
		!ft_strcmp(cmd_name, "/usr/bin/cd"))
		ft_cd(shell);
	else if (!ft_strcmp(low, "pwd") || \
		!ft_strcmp(low, "/bin/pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(low, "env") || \
		!ft_strcmp(low, "/usr/bin/env"))
		ft_env(shell);
	else if (!ft_strcmp(cmd_name, "export"))
		ft_export(shell);
	else if (!ft_strcmp(cmd_name, "unset"))
		ft_unset(shell);
	free(low);
}
