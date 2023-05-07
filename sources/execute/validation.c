/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/07 14:44:04 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_cmd(char *str)
{
	char	*s;

	s = ft_tolowercase(str);
	if (ft_strcmp(s, "cd") == 0 || \
		ft_strcmp(s, "pwd") == 0 || \
		ft_strcmp(s, "env") == 0 || \
		ft_strcmp(s, "echo") == 0 || \
		ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(s, "/usr/bin/cd") == 0 || \
		ft_strcmp(s, "/bin/pwd") == 0 || \
		ft_strcmp(s, "/usr/bin/env") == 0 || \
		ft_strcmp(s, "/bin/echo") == 0 || \
		ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(str, "exit") == 0)
	{
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

char	*check_cmd(char **cmd, char **path_list)
{
	char	*path;
	int		i;

	if (!cmd[0] || !*cmd[0] || !args_count(cmd))
		return (console(1, cmd[0], "command not found"), NULL);
	if (is_valid_cmd(cmd[0]))
		return (ft_strdup("builtin"));
	path = cmd[0];
	if (*cmd[0] == '/' || (*cmd[0] == '.' && *(cmd[0] + 1) == '/'))
	{
		if (access(path, F_OK) == 0)
			return (path);
		return (console(1, path, strerror(errno)), NULL);
	}
	i = -1;
	if (!path_list)
		return (console(1, cmd[0], "No such file or directory"), NULL);
	while (path_list[++i])
	{
		path = ft_concat(3, path_list[i], "/", cmd[0]);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (console(1, cmd[0], "command not found"), NULL);
}
