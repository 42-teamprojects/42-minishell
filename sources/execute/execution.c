/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/25 17:03:14 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(int i)
{
	struct stat	statt;

	if (!ft_strcmp((g_shell)->cmds[i]->path, "builtin"))
		exit(ft_exec_builtin(i));
	if (execve((g_shell)->cmds[i]->path, (g_shell)->cmds[i]->full_cmd,
			(g_shell)->env) == -1)
	{
		if (stat((g_shell)->cmds[i]->path, &statt) == -1)
		{
			ft_printf_fd(2, "minishell: No such file or directory\n");
			exit(127);
		}
		else if (!S_ISREG(statt.st_mode))
		{
			ft_printf_fd(2, "minishell: is a directory\n");
			exit(126);
		}
		else
		{
			console(1, (g_shell)->cmds[i]->name, strerror(errno));
			exit(1);
		}
	}
}

void	start_pipe(int i)
{
	t_rd	*rd;

	rd = (g_shell)->cmds[i]->redir;
	if (rd && (g_shell)->cmds[i]->path == NULL)
		exit(0);
	if (!rd && (g_shell)->cmds[i]->path == NULL)
		exit(127);
	redirect_pipe(i);
	close_pipes();
	if (rd && handle_redirection(rd))
		exit(1);
	if (ft_strcmp((g_shell)->cmds[i]->path, "redir"))
		execute_cmd(i);
	if (rd)
		rollback_fd(&g_shell);
	exit((g_shell)->status_code);
}

int	ft_exec(void)
{
	pid_t	pid;
	pid_t	*pids;
	int		state;
	int		i;

	pids = malloc(sizeof(pid_t) * (g_shell)->cmds_count);
	if (!pids)
		return (1);
	if (create_pipe())
		return (console(1, "", "failed creating pipes"), free(pids), 1);
	i = -1;
	while (++i < (g_shell)->cmds_count)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			return (free(pids), console(1, "", strerror(errno)), 1);
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			start_pipe(i);
		}
		pids[i] = pid;
	}
	close_pipes();
	i = -1;
	while (++i < (g_shell)->cmds_count)
		waitpid(pids[i], &state, 0);
	(g_shell)->status_code = WEXITSTATUS(state);
	signal(SIGINT, &sig_handler);
	return (free(pids), 0);
}

int	ft_exec_builtin(int i)
{
	char	*cmd_name;
	char	*low;

	cmd_name = ft_strdup((g_shell)->cmds[i]->name);
	low = ft_tolowercase(cmd_name);
	if (ft_strchr(cmd_name, '/') != NULL)
		cmd_name = remove_slashes(cmd_name);
	if (!ft_strcmp(low, "echo") || !ft_strcmp(low, "/bin/echo"))
		return (free(cmd_name), free(low), ft_echo(i));
	if (!ft_strcmp(low, "pwd") || !ft_strcmp(low, "/bin/pwd"))
		return (free(cmd_name), free(low), ft_pwd(i));
	if (!ft_strcmp(low, "env") || !ft_strcmp(low, "/usr/bin/env"))
		return (free(cmd_name), free(low), ft_env(i));
	if (!ft_strcmp(cmd_name, "cd") || !ft_strcmp(cmd_name, "/usr/bin/cd"))
		return (free(cmd_name), free(low), ft_cd(i));
	if (!ft_strcmp(cmd_name, "export"))
		return (free(cmd_name), free(low), ft_export(i));
	if (!ft_strcmp(cmd_name, "unset"))
		return (free(cmd_name), free(low), ft_unset(i));
	if (!ft_strcmp(cmd_name, "exit"))
		return (free(cmd_name), free(low), ft_exit(i));
	return (1);
}
