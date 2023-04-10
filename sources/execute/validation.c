/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/10 19:42:09 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_cmd_list(t_command *command)
{
	char	**cmd;
	int		i;
	int		j;

	cmd = malloc(sizeof(char *) * (command->argc + 2));
	cmd[0] = command->name;
	i = 1;
	j = -1;
	while (++j < command->argc)
	{
		cmd[i] = command->args[j];
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	is_valid_cmd(char *str)
{
	if (ft_strcmp(ft_tolowercase(str), "cd") == 0 || \
		ft_strcmp(ft_tolowercase(str), "pwd") == 0 || \
		ft_strcmp(ft_tolowercase(str), "env") == 0 || \
		ft_strcmp(ft_tolowercase(str), "echo") == 0 || \
		ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(ft_tolowercase(str), "/usr/bin/cd") == 0 || \
		ft_strcmp(ft_tolowercase(str), "/bin/pwd") == 0 || \
		ft_strcmp(ft_tolowercase(str), "/usr/bin/env") == 0 || \
		ft_strcmp(ft_tolowercase(str), "/bin/echo") == 0 || \
		ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

int	check_command(t_shell **shell, char *path, char **command)
{
	if (!ft_strcmp(command[0], "$?"))
		return (console(1, ft_itoa((*shell)->status_code), \
		"command not found"), 0);
	if (access(path, F_OK) == 0 && !is_valid_cmd(command[0]))
	{
		(*shell)->path = ft_strdup(path);
		(*shell)->full_cmd = command;
		return (1);
	}
	return (0);
}

int	check_cmd(t_command *command, t_shell **shell)
{
	char	*path;
	char	**cmd;
	int		i;

	cmd = make_cmd_list(command);
	if (!cmd[0] || !*cmd[0] || !args_count(cmd))
		return (not_found(cmd[0]), 0);
	i = -1;
	path = cmd[0];
	if (check_command(shell, path, cmd))
		return (free(path), 1);
	else
	{
		while ((*shell)->path_list[++i])
		{
			path = ft_concat(3, (*shell)->path_list[i], "/", cmd[0]);
			if (check_command(shell, path, cmd))
				return (free(path), 1);
			free(path);
		}
	}
	if (is_valid_cmd(cmd[0]))
		return (1);
	not_found(cmd[0]);
	return (0);
}

int	is_cmd_exist(t_command **commands, t_shell **shell)
{
	int	i;

	i = -1;
	while (++i < (*shell)->cmds_count)
	{
		if (!check_cmd(commands[i], shell))
			return (0);
	}
	return (1);
}
