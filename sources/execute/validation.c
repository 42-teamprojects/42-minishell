/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/18 18:45:09 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*check_cmd(char **cmd, char **path_list)
{
	char	*path;
	int		i;

	if (!cmd[0] || !*cmd[0] || !args_count(cmd))
		return (not_found(cmd[0]), NULL);
	if (is_valid_cmd(cmd[0]))
		return (ft_strdup("builtin"));
	path = ft_strdup(cmd[0]);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (access(path, F_OK) == 0 && !is_valid_cmd(path))
			return (path);
		return (console(1, path, "No such file or directory"), NULL);
	}
	i = -1;
	while (path_list[++i])
	{
		path = ft_concat(3, path_list[i], "/", cmd[0]);
		if (access(path, F_OK) == 0 && !is_valid_cmd(path))
			return (path);
	}
	free(path);
	return (not_found(cmd[0]), NULL);
}
