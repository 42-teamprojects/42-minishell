/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/07 14:49:29 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_shell **shell, int i)
{
	if (!ft_strcmp((*shell)->cmds[i]->path, "builtin"))
		exit(ft_exec_builtin(shell, i));
	if (execve((*shell)->cmds[i]->path, (*shell)->cmds[i]->full_cmd,
			(*shell)->env) == -1)
	{
		console(1, (*shell)->cmds[i]->path, strerror(errno));
		exit(1);
	}
}

void	start_pipe(t_shell **shell, int i)
{
	t_rd	*rd;

	rd = (*shell)->cmds[i]->redir;
	if (rd && (*shell)->cmds[i]->path == NULL)
		exit(0);
	if (!rd && (*shell)->cmds[i]->path == NULL)
		exit(127);
	redirect_pipe(shell, i);
	close_pipes(shell);
	if (rd && handle_redirection(rd, shell))
		exit(1);
	if (ft_strcmp((*shell)->cmds[i]->path, "redir"))
		execute_cmd(shell, i);
	if (rd)
		rollback_fd(shell);
	exit((*shell)->status_code);
}

int	ft_exec(t_shell **shell)
{
	pid_t	pid;
	pid_t	*pids;
	int		i;
	int		state;

	pids = malloc(sizeof(pid_t) * (*shell)->cmds_count);
	if (create_pipe(shell))
		console(1, "", "failed creating pipes");
	i = 0;
	while (i < (*shell)->cmds_count)
	{
		pid = fork();
		if (pid == -1)
			return (console(1, "", strerror(errno)), 1);
		else if (pid == 0)
			start_pipe(shell, i);
		pids[i] = pid;
		i++;
	}
	close_pipes(shell);
	i = -1;
	while (++i < (*shell)->cmds_count)
		waitpid(pids[i], &state, 0);
	(*shell)->status_code = WEXITSTATUS(state);
	return (0);
}

int	ft_exec_builtin(t_shell **shell, int i)
{
	char	*cmd_name;
	char	*low;

	cmd_name = (*shell)->cmds[i]->name;
	low = ft_tolowercase(cmd_name);
	if (ft_strchr(cmd_name, '/') != NULL)
		cmd_name = remove_slashes(cmd_name);
	if (!ft_strcmp(low, "echo") || !ft_strcmp(low, "/bin/echo"))
		return (ft_echo(shell, i));
	if (!ft_strcmp(low, "pwd") || !ft_strcmp(low, "/bin/pwd"))
		return (ft_pwd(shell, i));
	if (!ft_strcmp(low, "env") || !ft_strcmp(low, "/usr/bin/env"))
		return (ft_env(shell, i));
	if (!ft_strcmp(cmd_name, "cd") || !ft_strcmp(cmd_name, "/usr/bin/cd"))
		return (ft_cd(shell, i));
	if (!ft_strcmp(cmd_name, "export"))
		return (ft_export(shell, i));
	if (!ft_strcmp(cmd_name, "unset"))
		return (ft_unset(shell, i));
	if (!ft_strcmp(cmd_name, "exit"))
		return (ft_exit(shell, i));
	free(low);
	return (1);
}
