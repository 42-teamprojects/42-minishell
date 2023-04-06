/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/06 15:35:31 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_valid_cmd(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0 || \
		ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(str, "env") == 0 || ft_strcmp(str, "echo") == 0 || \
		ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "/bin/pwd") == 0 || \
		ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(str, "env") == 0 || ft_strcmp(str, "echo") == 0)
		return (1);
	return (0);
}

int	check_command(t_shell *shell, char *path, char **command)
{
	if (access(path, F_OK) == 0 && !is_valid_cmd(command[0]))
	{
		shell->path = ft_strdup(path);
		shell->cmd.full_cmd = dup_list(command);
		return (1);
	}
	return (0);
}

int	verify_input(char **command, t_shell *shell)
{
	char	*path = NULL;
	int		i;

	if (!command || !*command || !args_count(command))
		return (print404(command[0]), 0);
	i = -1;
	path = ft_strjoin_gnl(path, command[0]);
	if (check_command(shell, path, command))
		return (free(path), 1);
	else
	{
		while (shell->path_list[++i])
		{
			path = ft_strjoin(shell->path_list[i], "/");
			path = ft_strjoin_gnl(path, command[0]);
			if (check_command(shell, path, command))
				return (free(path), 1);
			free(path);
		}
	}
	if (is_valid_cmd(command[0]))
		return (1);
	print404(command[0]);
	return (0);
}
