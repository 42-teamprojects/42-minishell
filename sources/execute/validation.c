/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/26 13:34:34 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_valid_cmd(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0 || \
		ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(str, "env") == 0 || ft_strcmp(str, "echo") == 0)
		return (1);
	return (0);
}

int	verify_input(t_shell *shell, char *str)
{
	char	**paths;
	char	*path;
	char	**first_cmd;
	int		i;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	first_cmd = ft_split(str, ' ');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_gnl(path, first_cmd[0]);
		if (access(path, F_OK) == 0 && !is_valid_cmd(first_cmd[0]))
		{
			shell->path = ft_strdup(path);
			shell->cmd.full_cmd = dup_list(first_cmd);
			return (1);
		}
		free(path);
		i++;
	}
	if (is_valid_cmd(first_cmd[0]))
		return (1);
	printf(BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
	first_cmd[0]);
	return (free_split(first_cmd), free_split(paths), 0);
}
